#ifndef TASKDISTRIBUTOR_PRETTYPRINT_H
#define TASKDISTRIBUTOR_PRETTYPRINT_H

#include <iostream>
#include <vector>
#include <sstream>
#include <tuple>

template<typename T>
std::string vectorToString(const std::vector<T> &vector);

template<typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<std::vector<T>> &vector) {
    os << vectorToString(vector);
    return os;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &vector) {
    os << vectorToString(vector);
    return os;
}

template<typename T>
std::string vectorToString(const std::vector<T> &vector) {
    std::stringstream stringstream;
    stringstream << "{";
    for (int i = 0; i < vector.size(); ++i) {
        stringstream << vector[i];
        if (i != vector.size() - 1) {
            stringstream << ", ";
        }
    }
    stringstream << "}";
    return stringstream.str();
}


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
