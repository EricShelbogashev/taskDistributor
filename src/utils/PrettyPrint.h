#ifndef TASKDISTRIBUTOR_PRETTYPRINT_H
#define TASKDISTRIBUTOR_PRETTYPRINT_H

#include <iostream>
#include <vector>

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

#endif //TASKDISTRIBUTOR_PRETTYPRINT_H
