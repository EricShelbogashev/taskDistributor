#include "PrettyPrint.h"

std::ostream &operator<<(std::ostream &os, const GroupInfo::Role &role) {
    return os << static_cast<int>(role);
}
