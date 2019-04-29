#include <utility>

#include "ip.h"

namespace IpAddress_NS {

    FilterPartIPv4::FilterPartIPv4(size_t index, std::string value) : index(index), value(std::move(value)) {}

    string IPv4::getByIndex(size_t index) const {
        return ipv4.at(index);
    }

    bool operator<(const IpAddress_NS::IPv4 &lhs, const IPv4 &rhs) {
        for (size_t i = 0; i < 4; i++) {
            if (lhs.ipv4[i].size() != rhs.ipv4[i].size()) {
                return lhs.ipv4[i].size() < rhs.ipv4[i].size();
            }
            if (lhs.ipv4[i] != rhs.ipv4[i]) {
                return lhs.ipv4[i] < rhs.ipv4[i];
            }
        }

        return false;
    }

    std::ostream &operator<<(std::ostream &os, const IPv4 &ip_v4) {
        decltype(auto) ip_v4_iter = ip_v4.ipv4.cbegin();
        while (ip_v4_iter != ip_v4.ipv4.cend()) {
            os << *ip_v4_iter;
            ip_v4_iter++;
            if (ip_v4_iter != ip_v4.ipv4.cend()) {
                os << ".";
            }
        }

        return os;
    }

}