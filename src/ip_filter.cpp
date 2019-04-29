//#include <cassert>
//#include <cstdlib>
#include <iostream>
#include <istream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
//#include <iterator>
#include <algorithm>
#include "ip_address/ip.h"
#include "tool/tokenize.h"


int main() {

    try {

        std::ifstream f_read("../../ip_filter.tsv");
        if (!f_read) {
            return 1;
        }

        IpAddress_NS::PoolIPv4 ip_pool_;

        for (std::string line; std::getline(f_read, line);) {
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

        std::cout << " ============ TODO filter by first byte and output ============ " << std::endl;
        IpAddress_NS::PoolIPv4 tmp = ip_pool_.filter(IpAddress_NS::FilterPartIPv4{0, "1"});

        for (const auto &ip : tmp) {
            std::cout << ip << std::endl;
        }

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)

        std::cout << " ============ TODO filter by first and second bytes and output ============ " << std::endl;
        IpAddress_NS::PoolIPv4 tmp2 = ip_pool_.filter(IpAddress_NS::FilterPartIPv4{0, "46"},
                                                      IpAddress_NS::FilterPartIPv4{1, "70"});

        for (const auto &ip : tmp2) {
            std::cout << ip << std::endl;
        }

        // TODO filter by any byte and output
        // ip = filter_any(46)

        std::cout << " ============ TODO filter by any byte and output ============ " << std::endl;
        IpAddress_NS::PoolIPv4 tmp3 = ip_pool_.filterAny(IpAddress_NS::FilterPartIPv4{0, "46"},
                                                         IpAddress_NS::FilterPartIPv4{1, "46"},
                                                         IpAddress_NS::FilterPartIPv4{2, "46"},
                                                         IpAddress_NS::FilterPartIPv4{3, "46"});

        for (const auto &ip : tmp3) {
            std::cout << ip << std::endl;
        }
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}