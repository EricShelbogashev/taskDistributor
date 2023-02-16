#ifndef TASKDISTRIBUTOR_MATRIXBUILDER_H
#define TASKDISTRIBUTOR_MATRIXBUILDER_H

#include "Matrix.h"

class MatrixBuilder {
public:
    MatrixBuilder(size_t height, size_t width, bool transposedStore = false);

    void addDimension(const std::vector<std::vector<float>> &dimensions, size_t index);

    Matrix matrix() const;
private:
    Matrix _matrix;
};


#endif //TASKDISTRIBUTOR_MATRIXBUILDER_H
