#ifndef TASKDISTRIBUTOR_GROUPINFO_H
#define TASKDISTRIBUTOR_GROUPINFO_H


#include <boost/serialization/access.hpp>
#include <iostream>
#include <vector>

struct GroupInfo {
public:
    enum Role {
        DEFAULT,
        MAIN_ROW,
        MAIN_COLUMN
    };

    int row = -1;
    int column = -1;
    std::vector<Role> role;

    GroupInfo() = default;

    explicit GroupInfo(int row, int column) : row(row), column(column), role(3) {}

private:
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & this->row;
        ar & this->column;
        ar & this->role;
    };

};

class GroupInfoBuilder {
    friend class GroupInfo;

private:

    GroupInfo groupInfo;

public:

    explicit GroupInfoBuilder() = default;

    GroupInfoBuilder(const GroupInfoBuilder &other) = delete;

    GroupInfoBuilder &addRole(GroupInfo::Role role) {
        groupInfo.role.emplace_back(role);
        return *this;
    }

    GroupInfoBuilder &setRow(int row) {
        groupInfo.row = row;
        return *this;
    }

    GroupInfoBuilder &setColumn(int column) {
        groupInfo.column = column;
        return *this;
    }

    GroupInfo build() {
        return groupInfo;
    }

};

std::ostream &operator<<(std::ostream &os, const GroupInfo &groupInfo);

#endif //TASKDISTRIBUTOR_GROUPINFO_H
