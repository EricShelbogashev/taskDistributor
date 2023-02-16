#ifndef TASKDISTRIBUTOR_MATRIX_H
#define TASKDISTRIBUTOR_MATRIX_H

#include <iostream>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/cstdint.hpp>
#include <vector>

class Matrix {
    friend class MatrixWrapper;

public:
    explicit Matrix();

    explicit Matrix(size_t height, size_t width, bool transposedStore = false);

    Matrix(const Matrix &other);

    virtual ~Matrix() = default;

    float &operator()(size_t row, size_t column);

    float operator()(size_t row, size_t column) const;

    [[nodiscard]] size_t height() const;

    [[nodiscard]] size_t width() const;

    [[nodiscard]] const std::vector<std::vector<float>> &getDimensions() const;

private:
    size_t _raw_height;
    size_t _raw_width;

    void initData();
    void initData(const std::vector<std::vector<float>> &other);

    bool _transposedStore;
    std::vector<std::vector<float>> _dimensions;

    size_t _height;
    size_t _width;

    friend class boost::serialization::access;
    template<class Archive> void serialize(Archive &ar, const unsigned int version) {
        ar & this->_raw_height;
        ar & this->_raw_width;
        ar & this->_transposedStore;
        ar & this->_dimensions;
        ar & this->_height;
        ar & this->_width;
    };
};


#endif //TASKDISTRIBUTOR_MATRIX_H
