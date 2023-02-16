#ifndef TASKDISTRIBUTOR_MANAGERTASK_H
#define TASKDISTRIBUTOR_MANAGERTASK_H

#include "../libs/ProcessContainer.h"
#include "Matrix.h"
#include "boost/mpi.hpp"
#include <boost/serialization/vector.hpp>

namespace mpi = boost::mpi;

class ManagerTask : public ProcessContainer<void, const mpi::communicator &, const std::string &, const std::string &> {
public:
    ManagerTask(int argc, char **argv)
            : ProcessContainer<void, const mpi::communicator &, const std::string &, const std::string &>(argc, argv) {}

    void execute(const mpi::communicator &, const std::string &, const std::string &) override;
};


#endif //TASKDISTRIBUTOR_MANAGERTASK_H
