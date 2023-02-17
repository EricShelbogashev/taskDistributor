#ifndef TASKDISTRIBUTOR_GROUPINFO_H
#define TASKDISTRIBUTOR_GROUPINFO_H


#include <boost/serialization/access.hpp>
#include <iostream>

struct GroupInfo {
    enum Role {
        DEFAULT, MAIN_ROW, MAIN_COLUMN, MANAGER
    };

    GroupInfo() = default;

    GroupInfo(int row, int column, Role role = DEFAULT) :
            row(row), column(column), role(role) {}

    int row;
    int column;
    Role role;

private:
    friend class boost::serialization::access;
    template<class Archive> void serialize(Archive &ar, const unsigned int version) {
        ar & this->row;
        ar & this->column;
        ar & this->role;
    };
};

std::ostream &operator<<(std::ostream &os, const GroupInfo &groupInfo);

#endif //TASKDISTRIBUTOR_GROUPINFO_H
