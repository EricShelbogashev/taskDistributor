#include "GroupInfo.h"

std::ostream &operator<<(std::ostream &os, const GroupInfo &groupInfo) {
    os << "{ row=" << groupInfo.row << ", column=" << groupInfo.column << ", role=" << groupInfo.role << " }";
    return os;
}