#ifndef TASKDISTRIBUTOR_MATRIXUTILS_H
#define TASKDISTRIBUTOR_MATRIXUTILS_H

#include "../model/Matrix.h"

std::ostream &operator<<(std::ostream &os, const Matrix &matrix);

void randomFillMatrix(Matrix &matrix);

Matrix readMatrix(std::ifstream &stream);


#endif //TASKDISTRIBUTOR_MATRIXUTILS_H
