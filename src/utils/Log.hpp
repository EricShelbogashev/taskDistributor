#ifndef TASKDISTRIBUTOR_LOG_HPP
#define TASKDISTRIBUTOR_LOG_HPP

#include <string>
#include <ostream>
#include "Colormod.h"
#include "Format.h"

class Log {
public:
    template<typename ...Args>
    static void info(std::ostream &ostream, Args... args) {
        ostream << "[" << Color::Modifier(Color::Code::FG_GREEN) << "INFO"
                  << Color::Modifier(Color::Code::FG_DEFAULT) << "] ";
        ((ostream << args),...);
        ostream << std::endl;
    }

    template<typename ...Args>
    static void info(Args... args) {
        info(std::cout, args...);
    }
};


#endif //TASKDISTRIBUTOR_LOG_HPP
