#ifndef TASKDISTRIBUTOR_LOG_HPP
#define TASKDISTRIBUTOR_LOG_HPP

#include <string>
#include <ostream>
#include "Colormod.h"
#include "Format.h"
#include "PrettyPrint.h"

class Log {
public:
    template<typename ...Args>
    static void log(std::ostream &ostream, const Args&... args) {
        ostream << "[" << Color::Modifier(Color::Code::FG_BLUE) << "LOG"
                  << Color::Modifier(Color::Code::FG_DEFAULT) << "] ";
        ((ostream << args),...);
        ostream << std::endl;
    }

    template<typename ...Args>
    static void log(const Args&... args) {
        log(std::cout, args...);
    }

    template<typename ...Args>
    static void info(std::ostream &ostream, const Args&... args) {
        ostream << "[" << Color::Modifier(Color::Code::FG_GREEN) << "INFO"
                << Color::Modifier(Color::Code::FG_DEFAULT) << "] ";
        ((ostream << args),...);
        ostream << std::endl;
    }

    template<typename ...Args>
    static void info(const Args&... args) {
        info(std::cout, args...);
    }
};


#endif //TASKDISTRIBUTOR_LOG_HPP
