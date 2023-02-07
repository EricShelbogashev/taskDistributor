#ifndef LAB3_MATRIXTASK_H
#define LAB3_MATRIXTASK_H

#include "../libs/ProcessContainer.h"

class MatrixTask : public ProcessContainer {
public:
    MatrixTask(int argc, char **argv) : ProcessContainer(argc, argv) {}

    std::any execute() override;
};


#endif //LAB3_MATRIXTASK_H
