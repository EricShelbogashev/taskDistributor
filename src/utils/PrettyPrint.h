#ifndef TASKDISTRIBUTOR_PRETTYPRINT_H
#define TASKDISTRIBUTOR_PRETTYPRINT_H

#include <iostream>
#include <vector>
#include <sstream>
#include <tuple>
#include <unordered_set>
#include "../model/GroupInfo.h"

template<typename T, template<typename ...> class Container>
std::string containerToString(const Container<T> &container);

template<typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<std::vector<T>> &vector) {
    os << containerToString(vector);
    return os;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &vector) {
    os << containerToString(vector);
    return os;
}

template<typename T, template<typename ...> class Container>
std::string containerToString(const Container<T> &container) {
    std::stringstream stringstream;
    stringstream << "{";
    for (int i = 0; i < container.size(); ++i) {
        stringstream << container[i];
        if (i != container.size() - 1) {
            stringstream << ", ";
        }
    }
    stringstream << "}";
    return stringstream.str();
}


template<class T>
std::ostream &operator<<(std::ostream &os, const std::unordered_set<T> &set) {
    std::stringstream stringstream;
    stringstream << "{ ";
    for (auto &entry: set) {
        os << set << " ";
    }
    stringstream << "}";
    return os << stringstream.str();
}

std::ostream &operator<<(std::ostream &os, const GroupInfo::Role &role);

// https://stackoverflow.com/questions/6245735/pretty-print-stdtuple
template<class TupType, size_t... I>
void print(std::ostream &os, const TupType &_tup, std::index_sequence<I...>) {
    os << "(";
    (..., (os << (I == 0 ? "" : ", ") << std::get<I>(_tup)));
    os << ")";
}

template<class... T>
std::ostream &operator<<(std::ostream &os, const std::tuple<T...> &tuple) {
    print(os, tuple, std::make_index_sequence<sizeof...(T)>());
    return os;
}

template<typename T, typename U>
std::ostream &operator<<(std::ostream &os, const std::pair<T, U> &pair) {
    os << "(" << pair.first << ", " << pair.second << ")";
    return os;
}

#endif //TASKDISTRIBUTOR_PRETTYPRINT_H
