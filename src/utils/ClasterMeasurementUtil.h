#ifndef TASKDISTRIBUTOR_CLASTERMEASUREMENTUTIL_H
#define TASKDISTRIBUTOR_CLASTERMEASUREMENTUTIL_H


#include <vector>
#include "../model/Matrix.h"

class ClasterMeasurementUtil {
public:
    explicit ClasterMeasurementUtil(const Matrix &matrix, size_t processNumber);

    [[nodiscard]] std::vector<int> sizes() const;

    [[nodiscard]] std::vector<int> displacements() const;

    ClasterMeasurementUtil(const ClasterMeasurementUtil &other) = delete;

    ClasterMeasurementUtil(ClasterMeasurementUtil &&other) = delete;

private:
    size_t _processNumber;
    mutable std::vector<int> _sizes;
    mutable std::vector<int> _displacements;
    const Matrix &_matrix;
    mutable bool _is_sized = false;
    mutable bool _is_displacemented = false;

    [[nodiscard]] std::vector<int> _calculateSizes(const Matrix &matrix) const;
    [[nodiscard]] std::vector<int> _calculateDisplacements(const Matrix &matrix) const;
};


#endif //TASKDISTRIBUTOR_CLASTERMEASUREMENTUTIL_H
