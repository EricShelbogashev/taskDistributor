#ifndef TASKDISTRIBUTOR_CLUSTERMEASUREMENTUTIL_H
#define TASKDISTRIBUTOR_CLUSTERMEASUREMENTUTIL_H


#include <vector>
#include "../model/Matrix.h"

class ClusterMeasurementUtil {
public:
    explicit ClusterMeasurementUtil(const Matrix &matrix, size_t processNumber, bool reverseBalancing = false);

    [[nodiscard]] const std::vector<int> &sizes() const;

    [[nodiscard]] const std::vector<int> &displacements() const;

    ClusterMeasurementUtil(const ClusterMeasurementUtil &other) = delete;

    ClusterMeasurementUtil(ClusterMeasurementUtil &&other) = delete;

private:
    size_t _processNumber;
    mutable std::vector<int> _sizes;
    mutable std::vector<int> _displacements;
    const Matrix &_matrix;
    mutable bool _is_sized = false;
    mutable bool _is_displacemented = false;
    bool _reverseBalancing;
    [[nodiscard]] const std::vector<int> &_calculateSizes(const Matrix &matrix) const;
    [[nodiscard]] const std::vector<int> &_calculateDisplacements(const Matrix &matrix) const;
};


#endif //TASKDISTRIBUTOR_CLUSTERMEASUREMENTUTIL_H
