#pragma once

#include <ostream>
#include <vector>
#include <string>

namespace IpAddress_NS {
    using namespace std;

    struct FilterPartIPv4 {
        FilterPartIPv4(size_t index, const string &value);

        size_t index;
        string value;
    };

    enum class OperatorFilter {
        AND,
        OR
    };

    class IPv4 {
    public:
        IPv4(vector<string> ipv4) : ipv4(move(ipv4)) {}

        friend bool operator<(const IPv4 &lhs, const IPv4 &rhs);

        friend std::ostream &operator<<(std::ostream &os, const IPv4 &pv4);

        string getByIndex(size_t index) const;

    private:
        vector<string> ipv4;
    };

    class PoolIPv4 : public std::vector<IPv4> {
    public:
        template<typename ... Args>
        PoolIPv4 filter(Args... args) {
            PoolIPv4 filteredPool;
            for (const auto &ipv4 : *this) {
                if (condition(OperatorFilter::AND, ipv4, args...)) {
                    filteredPool.emplace_back(ipv4);
                }
            }
            return filteredPool;
        }

        template<typename ... Args>
        PoolIPv4 filterAny(Args... args) {
            PoolIPv4 filteredPool;
            for (const auto &ipv4 : *this) {
                if (condition(OperatorFilter::OR, ipv4, args...)) {
                    filteredPool.emplace_back(ipv4);
                }
            }
            return filteredPool;
        }

    private:
        bool condition(const OperatorFilter& of, const IPv4 &ipv4, const FilterPartIPv4 &part_value) {
            return ipv4.getByIndex(part_value.index) == part_value.value;
        }

        template<typename ... Args>
        bool
        condition(const OperatorFilter& of, const IPv4 &ipv4, const FilterPartIPv4 &part_value, const Args &... args) {
            if (of == OperatorFilter::AND) {
                return condition(of, ipv4, part_value) && condition(of, ipv4, args...);
            }
            return condition(of, ipv4, part_value) || condition(of, ipv4, args...);
        }
    };

} // namespace IpAddress_NS