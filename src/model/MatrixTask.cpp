#include <boost/mpi.hpp>
#include "MatrixTask.h"
#include "ManagerTask.h"
#include "../future/Package.h"
#include "../utils/Log.hpp"
#include "GroupInfo.h"
#include "CalculateTask.h"
#include "boost/serialization/unordered_set.hpp"

namespace mpi = boost::mpi;

MatrixTask::MatrixTask(int argc, char **argv) : ProcessContainer(argc, argv) {}

std::vector<std::vector<float>> receiveMatrix(const mpi::communicator &communicator, int &packagesNumber, int root) {

    mpi::scatter(communicator, packagesNumber, root);

    /* Getting matrix parties from root process. */
    std::vector<std::vector<float>> matrixPart(packagesNumber);
    mpi::scatterv(communicator,
                  matrixPart.data(),
                  packagesNumber,
                  root);

    return matrixPart;
}

template<typename U>
bool vectorContains(const std::vector<U> &vector, const U &element) {
    return std::find(vector.begin(), vector.end(), element) != vector.end();
}

void MatrixTask::execute(const boost::mpi::communicator &world, int root, const std::string &inFileName, const std::string &outFileName) {
    if (world.rank() == root) {
        ManagerTask manager(argc_, argv_);
        return manager.execute(world, inFileName, outFileName);
    }

    /* Preparing to receiving matrix parties from root process. */
    GroupInfo groupInfo{};
    boost::mpi::scatter(world, groupInfo, root);
    Log::log("Received groupInfo=", groupInfo);

    std::vector<std::vector<float>> matrixAPart;
    std::vector<std::vector<float>> matrixBPart;

    mpi::communicator communicatorColumn = vectorContains(groupInfo.role, GroupInfo::MAIN_COLUMN) ? world.split(groupInfo.column, 0) : world.split(groupInfo.column);
    mpi::communicator communicatorRow = vectorContains(groupInfo.role, GroupInfo::MAIN_ROW) ? world.split(groupInfo.row, 0) : world.split(groupInfo.row);
    if (vectorContains(groupInfo.role, GroupInfo::MAIN_COLUMN)) {
        int packagesNumber = -1;
        matrixAPart = receiveMatrix(communicatorColumn, packagesNumber, 0);

        /* 3rd stage from technical specification. */
        boost::mpi::broadcast(communicatorRow, matrixAPart, 0);
    } else {
        Log::error("ok");
        boost::mpi::broadcast(communicatorRow, matrixAPart, 0);
        Log::error("ok");
    }

    if (vectorContains(groupInfo.role, GroupInfo::MAIN_ROW)) {
        int packagesNumber = -1;
        matrixBPart = receiveMatrix(communicatorRow, packagesNumber, 0);

        /* 4th stage from technical specification. */
        boost::mpi::broadcast(communicatorColumn, matrixBPart, 0);
    } else {
        boost::mpi::broadcast(communicatorColumn, matrixBPart, 0);
    }

    Log::log("Rank=", world.rank(), ", Calculate input=", matrixAPart, " ", matrixBPart);

    CalculateTask calcTask(this->argc_, this->argv_);
    std::vector<std::vector<float>> matrixCPart = calcTask.execute(std::move(matrixAPart), std::move(matrixBPart));

    Log::log("Rank=", world.rank(), ", Calculate result=", matrixCPart);

    /* Sending matrix C parties to root process. */
    boost::mpi::gather(world, static_cast<int>(matrixCPart.size()), root);
    boost::mpi::gatherv(world, matrixCPart, root);
}