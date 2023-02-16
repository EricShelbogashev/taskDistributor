#ifndef TASKDISTRIBUTOR_MATRIXUTILS_H
#define TASKDISTRIBUTOR_MATRIXUTILS_H

#include "../model/Matrix.h"

std::ostream &operator<<(std::ostream &os, const Matrix &matrix);

namespace utils {
    void randomFillMatrix(Matrix &matrix);

    Matrix readMatrix(std::ifstream &stream);

    void saveMatrix(std::ostream &stream, const Matrix &matrix);
}

#endif //TASKDISTRIBUTOR_MATRIXUTILS_H
