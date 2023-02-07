#include "MatrixTask.h"
#include "mpi.h"

std::any MatrixTask::execute() {
    MPI_Init(&argc_, &argv_);
    std::cout << "Hello world!" << std::endl;
    MPI_Finalize();
    return {};
}