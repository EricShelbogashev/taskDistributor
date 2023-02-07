#ifndef LAB3_CONTAINTERMPI_H
#define LAB3_CONTAINTERMPI_H

#include <any>

class ProcessContainer {
public:
    ProcessContainer(int argc, char **argv): argc_(argc), argv_(argv) {}
    virtual ~ProcessContainer() = default;

    virtual std::any execute() = 0;

protected:
    int argc_;
    char **argv_;
};

#endif //LAB3_CONTAINTERMPI_H
