#include "ManagerTask.h"

#include <boost/mpi.hpp>
#include <fstream>
#include "../model/Cluster.h"
#include "../utils/ClusterMeasurementUtil.h"
#include "../utils/MatrixUtils.h"
#include "../utils/Log.hpp"
#include "GroupInfo.h"
#include "CalculateTask.h"

int &sendSizes(const mpi::communicator &communicator, const ClusterMeasurementUtil &measurementUtil) {
    static int packagesNumber;

    auto &sizes = measurementUtil.sizes();
//    Log::log(sizes);

    mpi::scatter(communicator, sizes, packagesNumber, communicator.rank());
    return packagesNumber;
}

void sendMatrix(const mpi::communicator &communicator, const ClusterMeasurementUtil &measurementUtil,
                std::vector<std::vector<float>> &dimensions, Matrix &matrix, int &packagesNumber) {
    /* Sending parties all non-root processes. */
    mpi::scatterv(communicator,
                  matrix.getDimensions(),
                  measurementUtil.sizes(),
                  measurementUtil.displacements(),
                  dimensions.data(),
                  packagesNumber,
                  communicator.rank());
}

void fillMinor(Matrix &res, size_t height, size_t width, size_t &globalOffset, size_t &offsetA, size_t &offsetB,
               const std::vector<std::vector<float>> &gathervResponse) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            res(offsetA + i, offsetB + j) = gathervResponse[globalOffset][j];
        }
        ++globalOffset;
    }
    offsetB += width;
}

Matrix buildMatrix(size_t height, size_t width, const std::vector<std::vector<float>> &gathervResponse,
                   const ClusterMeasurementUtil &measurementA, const ClusterMeasurementUtil &measurementB) {
    Matrix res(height, width);
    size_t offsetA = 0, offsetB = 0;
    size_t globalOffset = 0;
    for (int i: measurementA.sizes()) {
        for (int j: measurementB.sizes()) {
            fillMinor(res, i, j, globalOffset, offsetA, offsetB, gathervResponse);
        }
        offsetA += i;
        offsetB = 0;
    }
    return res;
}

std::vector<GroupInfo> getTableInfo(const Cluster &cluster) {
    std::vector<GroupInfo> tableInfo;
    for (int i = 0; i < cluster.getHeight(); ++i) {
        for (int j = 0; j < cluster.getWidth(); ++j) {
            const std::tuple<size_t, int, int> &r = cluster(i, j);
            GroupInfoBuilder groupInfoBuilder;
            groupInfoBuilder.setRow(std::get<1>(r)).setColumn(std::get<2>(r));
            if (i == 0) {
                groupInfoBuilder.addRole(GroupInfo::MAIN_ROW);
            }
            if (j == 0) {
                groupInfoBuilder.addRole(GroupInfo::MAIN_COLUMN);
            }
            if (i != 0 && j != 0) {
                groupInfoBuilder.addRole(GroupInfo::DEFAULT);
            }
            tableInfo.emplace_back(groupInfoBuilder.build());
        }
    }
    return tableInfo;
}

void
ManagerTask::execute(const mpi::communicator &world, const std::string &inFileName, const std::string &outFileName) {
    /* Getting matricies from file. */
    std::ifstream infile(inFileName);

    Matrix matrixA = utils::readMatrix(infile);
    Matrix matrixB = utils::readMatrix(infile);

    infile.close();
    Log::log("matrixA.width()=", matrixA.width());
    Log::log("matrixB.height()=", matrixB.height());
    assert(matrixA.width() == matrixB.height());

    Cluster &cluster = Cluster::instance();
    cluster.init(world.size(), world.rank());
    Log::log("Manager process with rank ", cluster.getRoot(), ".\n", cluster);

    /* Sending group log.  */
    std::vector<GroupInfo> tableInfo = getTableInfo(cluster);
    GroupInfo _tmp{};
    boost::mpi::scatter(world, tableInfo, _tmp, world.rank());

    mpi::communicator communicatorMainVertical = world.split(std::get<2>(cluster(0, 0)), 0);
    mpi::communicator communicatorMainHorizontal = world.split(std::get<1>(cluster(0, 0)), 0);

    /* (x, 0) - left main column. */
    Log::log("communicatorMainVertical.size()=", communicatorMainVertical.size());
    ClusterMeasurementUtil measurementA(matrixA, communicatorMainVertical.size());

    /* Preparing to sending matrix parties to first column processes. */
    int partSizeA = sendSizes(communicatorMainVertical, measurementA);

    /* Sending matrix parties to first column processes. */
    std::vector<std::vector<float>> matrixAPart(partSizeA);
    sendMatrix(communicatorMainVertical, measurementA, matrixAPart, matrixA, partSizeA);
    boost::mpi::broadcast(communicatorMainHorizontal, matrixAPart, 0);

    /* (0, y) - top main row. */
    Log::log("communicatorMainHorizontal.size()=", communicatorMainHorizontal.size());
    ClusterMeasurementUtil measurementB(matrixB, communicatorMainHorizontal.size(), true);

    /* Preparing to sending matrix parties to first row processes. */
    int partSizeB = sendSizes(communicatorMainHorizontal, measurementB);

    /* Sending matrix parties to first row processes. */
    std::vector<std::vector<float>> matrixBPart(partSizeB);
    sendMatrix(communicatorMainHorizontal, measurementB, matrixBPart, matrixB, partSizeB);

    boost::mpi::broadcast(communicatorMainVertical, matrixBPart, 0);
    Log::log("Rank=", world.rank(), "\t", matrixAPart, "\t", matrixBPart);

    CalculateTask calcTask(this->argc_, this->argv_);
    std::vector<std::vector<float>> matrixCPart = calcTask.execute(std::move(matrixAPart), std::move(matrixBPart));

    Log::log("Rank=", world.rank(), ", result=", matrixCPart);

    std::vector<int> sizes(world.size());
    boost::mpi::gather(world, static_cast<int>(matrixCPart.size()), sizes, world.rank());
    Log::log("Sizes=", sizes);
    std::vector<std::vector<float>> gathervResponse(std::accumulate(sizes.begin(), sizes.end(), 0));
    boost::mpi::gatherv(world, matrixCPart.data(), static_cast<int>(matrixCPart.size()), gathervResponse.data(), sizes,
                        world.rank());
    Log::log("Accumulated=", gathervResponse);

    Log::log("SizesA=", measurementA.sizes(), ", SizesB=", measurementB.sizes());
    Matrix resultMatrix = buildMatrix(matrixA.height(), matrixB.width(), gathervResponse, measurementA, measurementB);

    std::ofstream outFile(outFileName);
    utils::saveMatrix(outFile, resultMatrix);
    Log::log("matrix.height()=", resultMatrix.height(), ", matrix.width()=", resultMatrix.width(), "\n", resultMatrix);
    outFile.close();
}