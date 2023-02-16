#include "MatrixBuilder.h"

MatrixBuilder::MatrixBuilder(size_t height, size_t width, bool transposedStore) : _matrix(height, width, transposedStore) {}

void MatrixBuilder::addDimension(const std::vector<std::vector<float>> &dimensions, size_t index) {}

Matrix MatrixBuilder::matrix() const {
    return Matrix();
}

