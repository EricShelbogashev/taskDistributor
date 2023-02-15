#ifndef TASKDISTRIBUTOR_PACKAGE_H
#define TASKDISTRIBUTOR_PACKAGE_H

#include <vector>
#include <boost/serialization/access.hpp>
#include "cstdio"

template<typename T>
class Package {
private:
    void _storeIt(T arg) {
        _data.emplace_back(arg);
    }

    template<class ...Pkg>
    void _storeIt(T arg, Pkg... args) {
        _data.emplace_back(arg) = arg;
        return _storeIt(args...);
    }

    std::vector<T> _data;

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & this->_data;
    };

public:
    template<class ...Args>
    explicit Package(T arg, Args... args) {
        _storeIt(arg, args...);
    }

    Package() = default;
};


#endif //TASKDISTRIBUTOR_PACKAGE_H
