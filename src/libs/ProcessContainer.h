#ifndef LAB3_CONTAINTERMPI_H
#define LAB3_CONTAINTERMPI_H

#include <any>

template<class RetVal, class ...Args>
class ProcessContainer {
public:
    enum UnitType {
        MANAGER, WORKER
    };

    ProcessContainer(int argc, char **argv): argc_(argc), argv_(argv) {}
    virtual ~ProcessContainer() = default;

    virtual RetVal execute(Args... args) = 0;

protected:
    int argc_;
    char **argv_;
};

#endif //LAB3_CONTAINTERMPI_H
