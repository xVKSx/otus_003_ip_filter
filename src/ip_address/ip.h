#pragma once

#include <ostream>
#include <vector>
#include <string>

namespace IpAddress_NS {
    using namespace std;

    class IPv4 {
    public:
        explicit IPv4(vector<string> ipv4) : ipv4(move(ipv4)) {}

        friend bool operator<(const IPv4 &lhs, const IPv4 &rhs);

        friend std::ostream &operator<<(std::ostream &os, const IPv4 &pv4);

        string getByIndex(size_t index) const;

    private:
        vector<string> ipv4;
    };

    class PoolIPv4 : public std::vector<IPv4> {
    };

    enum class OperatorFilter {
        AND, OR
    };

    struct FilterPartIPv4 {
        FilterPartIPv4(size_t index, string value);

        size_t index;
        string value;
    };

    template<OperatorFilter T>
    class Condition {
    public:
        bool condition(const IPv4 &ipv4, const FilterPartIPv4 &part_value) {
            return ipv4.getByIndex(part_value.index) == part_value.value;
        }

        template<typename ... Args>
        bool condition(const IPv4 &ipv4, const FilterPartIPv4 &part_value, const Args &... args) {
            return condition(ipv4, part_value) && condition(ipv4, args...);
        }
    };

    template<>
    class Condition<OperatorFilter::OR> {
    public:
        bool condition(const IPv4 &ipv4, const FilterPartIPv4 &part_value) {
            return ipv4.getByIndex(part_value.index) == part_value.value;
        }

        template<typename ... Args>
        bool condition(const IPv4 &ipv4, const FilterPartIPv4 &part_value, const Args &... args) {
            return condition(ipv4, part_value) || condition(ipv4, args...);
        }
    };

    template<typename ... Args>
    PoolIPv4 filter(const PoolIPv4 &pool, const Args &... args) {
        PoolIPv4 filteredPool;
        for (const auto &ipv4 : pool) {
            if (Condition<OperatorFilter::AND>().condition(ipv4, args...))
                filteredPool.emplace_back(ipv4);
        }

        return filteredPool;
    }

    template<typename ... Args>
    PoolIPv4 filterAny(const PoolIPv4 &pool, const Args &... args) {
        PoolIPv4 filteredPool;
        for (const auto &ipv4 : pool) {
            if (Condition<OperatorFilter::OR>().condition(ipv4, args...))
                filteredPool.emplace_back(ipv4);
        }

        return filteredPool;
    }


} // namespace IpAddress_NS