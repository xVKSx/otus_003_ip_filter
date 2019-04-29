#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "ip.h"
#include "tokenize.h"

int main() {

    try {

        IpAddress_NS::PoolIPv4 ip_pool_;

        for (std::string line; std::getline(std::cin, line);) {
            std::vector<std::string> v = tokenize(line, '\t');
            ip_pool_.emplace_back(tokenize(v.at(0), '.'));
        }

        // TODO reverse lexicographically sort

        std::sort(ip_pool_.rbegin(), ip_pool_.rend());

        for (const auto &ip : ip_pool_) {
            std::cout << ip << std::endl;
        }

        // TODO filter by first byte and output
        // ip = filter(1)

        IpAddress_NS::PoolIPv4 filtered_pool_1 = ip_pool_.filter(IpAddress_NS::FilterPartIPv4{0, "1"});

        for (const auto &ip : filtered_pool_1) {
            std::cout << ip << std::endl;
        }

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)

        IpAddress_NS::PoolIPv4 filtered_pool_2 = ip_pool_.filter(IpAddress_NS::FilterPartIPv4{0, "46"},
                                                                         IpAddress_NS::FilterPartIPv4{1, "70"});

        for (const auto &ip : filtered_pool_2) {
            std::cout << ip << std::endl;
        }

        // TODO filter by any byte and output
        // ip = filter_any(46)

        IpAddress_NS::PoolIPv4 filtered_pool_3 = ip_pool_.filterAny(IpAddress_NS::FilterPartIPv4{0, "46"},
                                                         IpAddress_NS::FilterPartIPv4{1, "46"},
                                                         IpAddress_NS::FilterPartIPv4{2, "46"},
                                                         IpAddress_NS::FilterPartIPv4{3, "46"});

        for (const auto &ip : filtered_pool_3) {
            std::cout << ip << std::endl;
        }
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}