#ifndef LAB3_MATRIXTASK_H
#define LAB3_MATRIXTASK_H

#include "../libs/ProcessContainer.h"
#include "../model/Matrix.h"
#include <boost/mpi.hpp>

class MatrixTask : public ProcessContainer<void, const boost::mpi::communicator &, int, const std::string &, const std::string &> {
public:
    MatrixTask(int argc, char **argv);

    void execute(const boost::mpi::communicator &, int, const std::string &, const std::string &) override;
};


#endif //LAB3_MATRIXTASK_H
