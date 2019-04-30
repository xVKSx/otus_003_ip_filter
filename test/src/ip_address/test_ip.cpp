#define BOOST_TEST_MODULE ip_address_test

#include <istream>
#include <sstream>
#include <string>
#include <vector>
#include <boost/test/unit_test.hpp>

#include "../../../src/ip_address/ip.h"

BOOST_AUTO_TEST_SUITE(ip_address_test_suite)

    BOOST_AUTO_TEST_CASE(operator_lesser) {
        using namespace IpAddress_NS;
        BOOST_CHECK(IPv4({"1", "2", "1", "1"}) < IPv4({"1", "10", "1", "1"}));
        BOOST_CHECK(IPv4({"1", "1", "1", "1"}) < IPv4({"1", "2", "1", "1"}));
    }

    BOOST_AUTO_TEST_CASE(filter) {
        using namespace IpAddress_NS;
        PoolIPv4 pool;
        pool.emplace_back(IPv4({"1", "2", "3", "4"}));
        pool.emplace_back(IPv4({"2", "12", "13", "14"}));
        pool.emplace_back(IPv4({"1", "10", "1", "14"}));
        pool.emplace_back(IPv4({"20", "20", "113", "213"}));

        auto filteredPool1 = IpAddress_NS::filter(pool, IpAddress_NS::FilterPartIPv4{0, "1"});
        BOOST_CHECK_EQUAL(filteredPool1.size(), 2);

        auto filteredPool2 = IpAddress_NS::filter(pool, IpAddress_NS::FilterPartIPv4{2, "13"});
        BOOST_CHECK_EQUAL(filteredPool2.size(), 1);

        auto filteredPool3 = IpAddress_NS::filter(pool,
                                                  IpAddress_NS::FilterPartIPv4{0, "1"},
                                                  IpAddress_NS::FilterPartIPv4{3, "14"});
        BOOST_CHECK_EQUAL(filteredPool3.size(), 1);

        auto filteredPool4 = IpAddress_NS::filter(pool,
                                                  IpAddress_NS::FilterPartIPv4{0, "1"},
                                                  IpAddress_NS::FilterPartIPv4{3, "13"});
        BOOST_CHECK_EQUAL(filteredPool4.size(), 0);
    }

    BOOST_AUTO_TEST_CASE(filter_any) {
        using namespace IpAddress_NS;
        PoolIPv4 pool;
        pool.emplace_back(IPv4({"1", "2", "3", "4"}));
        pool.emplace_back(IPv4({"2", "12", "13", "14"}));
        pool.emplace_back(IPv4({"1", "10", "1", "14"}));
        pool.emplace_back(IPv4({"20", "20", "113", "213"}));

        auto filteredPool1 = IpAddress_NS::filterAny(pool, IpAddress_NS::FilterPartIPv4{0, "1"});
        BOOST_CHECK_EQUAL(filteredPool1.size(), 2);

        auto filteredPool2 = IpAddress_NS::filterAny(pool,
                                                     IpAddress_NS::FilterPartIPv4{0, "1"},
                                                     IpAddress_NS::FilterPartIPv4{2, "13"});
        BOOST_CHECK_EQUAL(filteredPool2.size(), 3);

        auto filteredPool3 = IpAddress_NS::filterAny(pool,
                                                     IpAddress_NS::FilterPartIPv4{0, "10"},
                                                     IpAddress_NS::FilterPartIPv4{3, "15"});
        BOOST_CHECK_EQUAL(filteredPool3.size(), 0);
    }

BOOST_AUTO_TEST_SUITE_END()
