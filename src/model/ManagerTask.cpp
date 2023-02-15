#include "ManagerTask.h"

#include <boost/mpi.hpp>
#include "../future/Package.h"
#include "../utils/MatrixUtils.h"
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

Matrix ManagerTask::execute(const mpi::communicator &communicator) {
    /* Getting matricies from file. */
    std::ifstream infile(this->argv_[1]);
    Matrix matrixA = readMatrix(infile);
    Matrix matrixB = readMatrix(infile);
    infile.close();
    assert(matrixA.width() == matrixB.height());

    /* Sending first matrix to all non-root processes. */
    mpi::broadcast(communicator, matrixA, communicator.rank());

    /* Preparing to sending matrix parties all non-root processes. */
    int packagesNumber = -1;
    auto conf = getScatterMeasurement(static_cast<int>(matrixB.width()), communicator.size());
    assert(conf.first.size() == communicator.size());

    mpi::scatter(communicator, conf.first, packagesNumber, communicator.rank());

    /* Sending matrix parties all non-root processes. */
    std::vector<std::vector<float>> matrixBPart(packagesNumber);
    mpi::scatterv(communicator,
                  matrixB.getDimensions(),
                  conf.first,
                  conf.second,
                  matrixBPart.data(),
                  packagesNumber,
                  communicator.rank());

    return Matrix(0, 0);
}