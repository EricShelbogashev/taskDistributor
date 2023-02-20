#include <fstream>
#include "src/model/MatrixTask.h"
#include "src/utils/Log.hpp"

namespace mpi = boost::mpi;

int main(int argc, char **argv) {
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
