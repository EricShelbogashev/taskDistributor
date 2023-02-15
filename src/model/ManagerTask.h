#ifndef TASKDISTRIBUTOR_MANAGERTASK_H
#define TASKDISTRIBUTOR_MANAGERTASK_H

#include "../libs/ProcessContainer.h"
#include "Matrix.h"
#include "boost/mpi.hpp"
#include <boost/serialization/vector.hpp>

namespace mpi = boost::mpi;

class ManagerTask : public ProcessContainer<Matrix, const mpi::communicator &> {
public:
    ManagerTask(int argc, char **argv)
            : ProcessContainer<Matrix, const mpi::communicator &>(argc, argv) {}

    Matrix execute(const mpi::communicator &) override;
};


#endif //TASKDISTRIBUTOR_MANAGERTASK_H
