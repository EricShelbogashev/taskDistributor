#include "MatrixTask.h"
#include "ManagerTask.h"
#include "../future/Package.h"
#include <boost/mpi.hpp>
#include "../utils/MatrixUtils.h"
#include "CalculateTask.h"
#include "MatrixBuilder.h"
#include "../utils/Log.hpp"

namespace mpi = boost::mpi;

MatrixTask::MatrixTask(int argc, char **argv) : ProcessContainer(argc, argv) {}

std::vector<std::vector<float>> receiveMatrix(const mpi::communicator &communicator, int &packagesNumber, int root) {

    mpi::scatter(communicator, packagesNumber, root);
//    Log::info("Rank=", communicator.rank(), ", ", "packagesNumber=", packagesNumber);

    /* Getting matrix parties from root process. */
    std::vector<std::vector<float>> matrixPart(packagesNumber);
    mpi::scatterv(communicator,
                  matrixPart.data(),
                  packagesNumber,
                  root);

    return matrixPart;
}

void MatrixTask::execute(const boost::mpi::communicator &communicator, int root, const std::string &inFileName, const std::string &outFileName) {
    if (communicator.rank() == root) {
        ManagerTask manager(argc_, argv_);
        return manager.execute(communicator, inFileName, outFileName);
    }

    /* Preparing to getting matrix parties from root process. */
    int packagesNumber = -1;

    /* Getting matrix A parties from root process. */
    auto matrixAPart = receiveMatrix(communicator, packagesNumber, root);

    /* Getting matrix B parties from root process. */
    auto matrixBPart = receiveMatrix(communicator, packagesNumber, root);

    CalculateTask calcTask(this->argc_, this->argv_);
    std::vector<std::vector<float>> matrixCPart = calcTask.execute(std::move(matrixAPart), std::move(matrixBPart));

    /* Sending matrix C parties to root process. */
    boost::mpi::gatherv(communicator, matrixCPart, root);
}