#ifndef TASKDISTRIBUTOR_MATRIXUTILS_CPP
#define TASKDISTRIBUTOR_MATRIXUTILS_CPP

#include <random>
#include <fstream>
#include "../model/Matrix.h"

std::ostream &operator<<(std::ostream &os, const Matrix &matrix) {
    for (int i = 0; i < matrix.height(); ++i) {
        for (int j = 0; j < matrix.width(); ++j) {
            os << matrix(i, j) << "\t";
        }
        if (i != matrix.height() - 1) {
            os << std::endl;
        }
    }
    return os;
}

void randomFillMatrix(Matrix &matrix) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist100(1,100);
    for (int i = 0; i < matrix.height(); ++i) {
        for (int j = 0; j < matrix.width(); ++j) {
            matrix(i, j) = static_cast<float>(dist100(rng));
        }
    }
}

/*  Matrix matrixA(4,23);
    Matrix matrixB(23,17, true);
    randomFillMatrix(matrixA);
    randomFillMatrix(matrixB); */

Matrix readMatrix(std::ifstream &stream) {
    size_t height, width, transpose;
    stream >> height;
    stream >> width;
    stream >> transpose;
    Matrix res(height, width, transpose);
    for (int i = 0; i < res.height(); ++i) {
        for (int j = 0; j < res.width(); ++j) {
            stream >> res(i, j);
        }
    }
    return res;
}

#endif //TASKDISTRIBUTOR_MATRIXUTILS_CPP
