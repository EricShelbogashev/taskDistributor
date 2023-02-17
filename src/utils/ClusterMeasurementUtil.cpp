#include "ClusterMeasurementUtil.h"
#include "Log.hpp"
#include <cmath>

ClusterMeasurementUtil::ClusterMeasurementUtil(const Matrix &matrix, size_t processNumber, bool reverseBalancing) :
        _matrix(matrix), _processNumber(processNumber), _sizes(processNumber), _displacements(processNumber),
        _reverseBalancing(reverseBalancing) {}

const std::vector<int> &ClusterMeasurementUtil::sizes() const {
    if (!_is_sized) {
        _is_sized = true;
        return _calculateSizes(_matrix);
    }
    return _sizes;
}

const std::vector<int> &ClusterMeasurementUtil::_calculateSizes(const Matrix &matrix) const {
    auto dimensionNumber = matrix.getDimensions().size();

    for (int i = 0; i < _processNumber; ++i) {
        _sizes[i] = static_cast<int>(dimensionNumber / _processNumber);
    }
    int lim = dimensionNumber - (dimensionNumber / _processNumber * _processNumber);
    if (_reverseBalancing) {
        for (int i = 0; i < lim; ++i) {
            _sizes[_sizes.size() - i - 1] += 1;
        }
    } else {
        for (int i = 0; i < lim; ++i) {
            _sizes[i] += 1;
        }
    }
    return _sizes;
}

const std::vector<int> &ClusterMeasurementUtil::displacements() const {
    if (!_is_displacemented) {
        _is_displacemented = true;
        return _calculateDisplacements(_matrix);
    }
    return _displacements;
}

const std::vector<int> &ClusterMeasurementUtil::_calculateDisplacements(const Matrix &matrix) const {
    // Checking for _instance.
    std::vector<int> sizesArr = sizes();
    for (int i = 1; i < _processNumber; ++i) {
        _displacements[i] = _displacements[i-1] + sizesArr[i];
    }
    return _displacements;
}
