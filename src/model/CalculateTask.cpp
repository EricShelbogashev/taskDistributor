#include "CalculateTask.h"

std::vector<std::vector<float>> CalculateTask::execute(const std::vector<std::vector<float>> &&matrixAPart,
                                                       const std::vector<std::vector<float>> &&matrixBPart) {
    if (matrixAPart.empty() || matrixBPart.empty()) {
        return {};
    }
    size_t len = matrixAPart[0].size();
    std::vector<std::vector<float>> result(matrixAPart.size());
    for (int i = 0; i < matrixAPart.size(); ++i) {
        result[i].resize(matrixBPart.size());
        for (int j = 0; j < matrixBPart.size(); ++j) {
            float sum = 0;
            for (int k = 0; k < len; ++k) {
                sum += matrixAPart[i][k] * matrixBPart[j][k];
            }
            result[i][j] = sum;
        }
    }
    return result;
}

CalculateTask::CalculateTask(int argc, char **argv) : ProcessContainer(argc, argv) {

}
