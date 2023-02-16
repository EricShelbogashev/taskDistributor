#include "ClasterMeasurementUtil.h"
#include <cmath>

ClasterMeasurementUtil::ClasterMeasurementUtil(const Matrix &matrix, size_t processNumber) :
        _matrix(matrix), _processNumber(processNumber), _sizes(processNumber), _displacements(processNumber) {}

std::vector<int> ClasterMeasurementUtil::sizes() const {
    if (!_is_sized) {
        _is_sized = true;
        return _calculateSizes(_matrix);
    }
    return _sizes;
}

std::vector<int> ClasterMeasurementUtil::_calculateSizes(const Matrix &matrix) const {
    auto dimensionNumber = matrix.getDimensions().size();

    for (int i = 0; i < _processNumber; ++i) {
        _sizes[i] = static_cast<int>(dimensionNumber / _processNumber);
    }
    for (int i = 0; i < dimensionNumber - (dimensionNumber / _processNumber * _processNumber); ++i) {
        _sizes[i] += 1;
    }
    return _sizes;
}

std::vector<int> ClasterMeasurementUtil::displacements() const {
    if (!_is_displacemented) {
        _is_displacemented = true;
        return _calculateDisplacements(_matrix);
    }
    return _displacements;
}

std::vector<int> ClasterMeasurementUtil::_calculateDisplacements(const Matrix &matrix) const {
    // Checking for instance.
    std::vector<int> sizesArr = sizes();
    for (int i = 1; i < _processNumber; ++i) {
        _displacements[i] = _displacements[i-1] + sizesArr[i];
    }
    return _displacements;
}
