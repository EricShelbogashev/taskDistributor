#include "CalculateTask.h"

std::vector<float> CalculateTask::execute(const std::vector<std::vector<float>> &&matrixAPart,
                                                       const std::vector<std::vector<float>> &&matrixBPart) {
    if (matrixAPart.empty() || matrixBPart.empty()) {
        return {};
    }
    size_t len = matrixAPart[0].size();
    std::vector<float> result;
    for (const auto & elemA : matrixAPart) {
        for (const auto & elemB : matrixBPart) {
            float sum = 0;
            for (int k = 0; k < len; ++k) {
                sum += elemA[k] * elemB[k];
            }
            result.emplace_back(sum);
        }
    }
    return result;
}

CalculateTask::CalculateTask(int argc, char **argv) : ProcessContainer(argc, argv) {

}
