#include <fstream>
#include "src/model/MatrixTask.h"
#include "src/utils/Log.hpp"
#include "src/utils/MatrixUtils.h"
namespace mpi = boost::mpi;

int main(int argc, char **argv) {
/*
    Matrix matrix(100, 100);
    utils::randomFillMatrix(matrix);
    std::ofstream outFile("input.txt");
    outFile << "100 100 0" << std::endl;
    utils::saveMatrix(outFile, matrix);
    outFile << "100 100 1" << std::endl;
    utils::randomFillMatrix(matrix);
    utils::saveMatrix(outFile, matrix);
    outFile.close();*/

    if (argc != 3) {
        std::cout << "Invalid args." << std::endl;
        return 0;
    }
    mpi::environment environment(argc, argv);
    mpi::communicator world;

    MatrixTask container(argc, argv);
    auto timer = mpi::timer();
    container.execute(world, 0, argv[1], argv[2]);
    Log::info("The process[", world.rank(), "] took \"", timer.elapsed(), " seconds to run.");
    return 0;
}
