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
    static void  printer(std::ostream &ostream, const std::string &type, const Color::Code &code, const Args&... args) {
        ostream << "[" << Color::Modifier(code) << type
                << Color::Modifier(Color::Code::FG_DEFAULT) << "] ";
        ((ostream << args),...);
        ostream << std::endl;
    }

    template<typename ...Args>
    static void log(const Args&... args) {
        printer(std::cout, "LOG", Color::Code::FG_BLUE, args...);
    }

    template<typename ...Args>
    static void info(const Args&... args) {
        printer(std::cout, "INFO", Color::Code::FG_GREEN, args...);
    }

    template<typename ...Args>
    static void error(const Args&... args) {
        printer(std::cout, "ERROR", Color::Code::FG_RED, args...);
    }
};


#endif //TASKDISTRIBUTOR_LOG_HPP
