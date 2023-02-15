#include "MatrixTask.h"
#include "ManagerTask.h"
#include "../future/Package.h"
#include <boost/mpi.hpp>
#include "../utils/MatrixUtils.h"

namespace mpi = boost::mpi;

MatrixTask::MatrixTask(int argc, char **argv) : ProcessContainer(argc, argv) {}

Matrix MatrixTask::execute(const boost::mpi::communicator &communicator, int root) {
    if (communicator.rank() == root) {
        ManagerTask manager(argc_, argv_);
        return manager.execute(communicator);
    }

    /* Receiving first matrix from root process. */
    Matrix matrixA;
    mpi::broadcast(communicator, matrixA, root);

    /* Preparing to getting matrix parties from root process. */
    int packagesNumber = -1;
    mpi::scatter(communicator, packagesNumber, root);

    /* Getting matrix parties from root process. */
    std::vector<std::vector<float>> matrixBPart(packagesNumber);
    mpi::scatterv(communicator,
                  matrixBPart.data(),
                  packagesNumber,
                  root);

    return Matrix(0, 0);
}