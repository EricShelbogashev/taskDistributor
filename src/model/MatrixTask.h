#ifndef LAB3_MATRIXTASK_H
#define LAB3_MATRIXTASK_H

#include "../libs/ProcessContainer.h"
#include "../model/Matrix.h"
#include <boost/mpi.hpp>

class MatrixTask : public ProcessContainer<Matrix, const boost::mpi::communicator &, int> {
public:
    MatrixTask(int argc, char **argv);

    Matrix execute(const boost::mpi::communicator &, int) override;
};


#endif //LAB3_MATRIXTASK_H
