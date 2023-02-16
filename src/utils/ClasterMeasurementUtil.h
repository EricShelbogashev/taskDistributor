#ifndef TASKDISTRIBUTOR_CLASTERMEASUREMENTUTIL_H
#define TASKDISTRIBUTOR_CLASTERMEASUREMENTUTIL_H


#include <vector>
#include "../model/Matrix.h"

class ClasterMeasurementUtil {
public:
    explicit ClasterMeasurementUtil(size_t processNumber);

    [[nodiscard]] std::vector<int> calculateSizes(const Matrix &matrix) const;

    [[nodiscard]] std::vector<int> calculateDisplacements(const Matrix &matrix) const;
private:
    size_t _processNumber;
};


#endif //TASKDISTRIBUTOR_CLASTERMEASUREMENTUTIL_H
