#include "Matrix.h"

Matrix::Matrix(size_t height, size_t width, bool transposedStore) :
        _raw_height(transposedStore ? width : height),
        _raw_width(transposedStore ? height : width),
        _height(height),
        _width(width),
        _transposedStore(transposedStore) {
    initData();
}

float &Matrix::operator()(size_t row, size_t column) {
    if (!_transposedStore) {
        return _dimensions[row][column];
    } else {
        return _dimensions[column][row];
    }
}

float Matrix::operator()(size_t row, size_t column) const {
    if (!_transposedStore) {
        return _dimensions[row][column];
    } else {
        return _dimensions[column][row];
    }
}

size_t Matrix::height() const {
    return _height;
}

size_t Matrix::width() const {
    return _width;
}

Matrix::Matrix(const Matrix &other) : _raw_width(other._raw_width), _raw_height(other._raw_height),
                                      _transposedStore(other._transposedStore),
                                      _height(other._height), _width(other._width) {
    initData(other._dimensions);
}

void Matrix::initData(const std::vector<std::vector<float>> &other) {
    _dimensions.resize(_raw_height);
    for (int i = 0; i < _raw_height; ++i) {
        _dimensions[i] = other[i];
    }
}

void Matrix::initData() {
    _dimensions.resize(_raw_height);
    for (int i = 0; i < _raw_height; ++i) {
        _dimensions[i].resize(_raw_width);
    }
}

const std::vector<std::vector<float>> &Matrix::getDimensions() const {
    return _dimensions;
}

Matrix::Matrix() :
        _raw_height(-1),
        _raw_width(-1),
        _height(-1),
        _width(-1),
        _transposedStore(false) {
}
