#include "ManagerTask.h"

#include <boost/mpi.hpp>
#include "../utils/MatrixUtils.h"
#include "../utils/ClasterMeasurementUtil.h"
#include "CalculateTask.h"
#include "MatrixBuilder.h"
#include <fstream>

std::pair<std::vector<int>, std::vector<int>> getScatterMeasurement(int dimensionNumber, int procNumber) {
    std::vector<int> sizes(procNumber);
    std::vector<int> displs(procNumber);
    bool flag = dimensionNumber - (dimensionNumber / procNumber) * procNumber > procNumber / 2;
    for (int i = 0; i < procNumber; ++i) {
        sizes[i] = (dimensionNumber / procNumber) + flag;
        displs[i] = i == 0 ? 0 : displs[i - 1] + sizes[i];
    }
    sizes[sizes.size() - 1] += dimensionNumber % ((dimensionNumber / procNumber) * procNumber) - flag * procNumber;

    std::pair<std::vector<int>, std::vector<int>> result(sizes, displs);
    return result;
}

void sendMatrix(const mpi::communicator &communicator, const ClasterMeasurementUtil &measurementUtil, std::vector<std::vector<float>> &dimensions, Matrix &matrix, int &packagesNumber) {

    auto sizes = measurementUtil.calculateSizes(matrix);
    mpi::scatter(communicator, sizes, packagesNumber, communicator.rank());

    /* Sending parties all non-root processes. */
    mpi::scatterv(communicator,
                  matrix.getDimensions(),
                  measurementUtil.calculateSizes(matrix),
                  measurementUtil.calculateDisplacements(matrix),
                  dimensions.data(),
                  packagesNumber,
                  communicator.rank());
}

Matrix ManagerTask::execute(const mpi::communicator &communicator) {
    /* Getting matricies from file. */
    std::ifstream infile(this->argv_[1]);
    Matrix matrixA = readMatrix(infile);
    Matrix matrixB = readMatrix(infile);
    infile.close();
    assert(matrixA.width() == matrixB.height());

    int packagesNumber = -1;
    /* Preparing to sending matrix parties all non-root processes. */
    ClasterMeasurementUtil measurementUtil(communicator.size());

    /* Sending matrix A parties all non-root processes. */
    std::vector<std::vector<float>> matrixAPart(packagesNumber);
    sendMatrix(communicator, measurementUtil, matrixAPart, matrixA, packagesNumber);

    /* Sending matrix B parties all non-root processes. */
    std::vector<std::vector<float>> matrixBPart(packagesNumber);
    sendMatrix(communicator, measurementUtil, matrixBPart, matrixB, packagesNumber);

    CalculateTask calcTask(this->argc_, this->argv_);
    std::vector<std::vector<float>> matrixCPart = calcTask.execute(std::move(matrixAPart), std::move(matrixBPart));

    /* Getting matrix C parties from non-root processes. */
    std::vector<std::vector<float>> gathervResponse(matrixA.height());
    boost::mpi::gatherv(communicator, matrixCPart, gathervResponse.data(), measurementUtil.calculateSizes(matrixA), communicator.rank());

    /* Construct result matrix. */
    MatrixBuilder matrixBuilder(matrixA.height(), matrixB.width());
    matrixBuilder.addDimension(gathervResponse, 0);

    return matrixBuilder.matrix();
}