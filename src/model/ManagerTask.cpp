#include "ManagerTask.h"

#include <boost/mpi.hpp>
#include "../utils/ClusterMeasurementUtil.h"
#include "../utils/MatrixUtils.h"
#include "CalculateTask.h"
#include "MatrixBuilder.h"
#include <fstream>
#include "../utils/PrettyPrint.h"
#include "../utils/Log.hpp"

int &sendSizes(const mpi::communicator &communicator, const ClusterMeasurementUtil &measurementUtil) {
    static int packagesNumber;

    auto sizes = measurementUtil.sizes();
    Log::info(sizes);

    mpi::scatter(communicator, sizes, packagesNumber, communicator.rank());
    return packagesNumber;
}

void sendMatrix(const mpi::communicator &communicator, const ClusterMeasurementUtil &measurementUtil, std::vector<std::vector<float>> &dimensions, Matrix &matrix, int &packagesNumber) {
    /* Sending parties all non-root processes. */
    mpi::scatterv(communicator,
                  matrix.getDimensions(),
                  measurementUtil.sizes(),
                  measurementUtil.displacements(),
                  dimensions.data(),
                  packagesNumber,
                  communicator.rank());
}

void ManagerTask::execute(const mpi::communicator &communicator, const std::string &inFileName, const std::string &outFileName) {
    /* Getting matricies from file. */
    std::ifstream infile(inFileName);

    Matrix matrixA = utils::readMatrix(infile);
    Matrix matrixB = utils::readMatrix(infile);

    infile.close();
    assert(matrixA.width() == matrixB.height());

    /* Preparing to sending matrix parties all non-root processes. */
    ClusterMeasurementUtil measurementA(matrixA, communicator.size());

    int &packagesNumber = sendSizes(communicator, measurementA);

    /* Sending matrix A parties all non-root processes. */
    std::vector<std::vector<float>> matrixAPart(packagesNumber);
    sendMatrix(communicator, measurementA, matrixAPart, matrixA, packagesNumber);

    /* Sending matrix B parties all non-root processes. */
    ClusterMeasurementUtil measurementB(matrixB, communicator.size());
    sendSizes(communicator, measurementB);

    std::vector<std::vector<float>> matrixBPart(packagesNumber);
    sendMatrix(communicator, measurementB, matrixBPart, matrixB, packagesNumber);

    CalculateTask calcTask(this->argc_, this->argv_);
    std::vector<std::vector<float>> matrixCPart = calcTask.execute(std::move(matrixAPart), std::move(matrixBPart));

    /* Getting matrix C parties from non-root processes. */
    std::vector<std::vector<float>> gathervResponse(matrixA.height());
    boost::mpi::gatherv(communicator, matrixCPart, gathervResponse.data(), measurementA.sizes(), communicator.rank());

    /* Construct result matrix. */
    MatrixBuilder matrixBuilder(matrixA.height(), matrixB.width());
    matrixBuilder.addDimension(gathervResponse, 0);

    std::ofstream outFile(outFileName);
    utils::saveMatrix(outFile, matrixBuilder.matrix());
    outFile.close();
}