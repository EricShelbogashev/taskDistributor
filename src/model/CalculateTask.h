#ifndef TASKDISTRIBUTOR_CALCULATETASK_H
#define TASKDISTRIBUTOR_CALCULATETASK_H

#include <vector>
#include "../libs/ProcessContainer.h"
#include "Matrix.h"

class CalculateTask
        : public ProcessContainer<std::vector<float>, const std::vector<std::vector<float>> &&, const std::vector<std::vector<float>> &&> {
public:
    explicit CalculateTask(int argc, char **argv);
    std::vector<float> execute(const std::vector<std::vector<float>> &&matrixAPart, const std::vector<std::vector<float>> &&matrixBPart) override;
};


#endif //TASKDISTRIBUTOR_CALCULATETASK_H
