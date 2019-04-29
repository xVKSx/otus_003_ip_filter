#define BOOST_TEST_MODULE tokenize_test

#include <istream>
#include <sstream>
#include <string>
#include <vector>
#include <boost/test/unit_test.hpp>

#include "../../../src/tool/tokenize.h"

BOOST_AUTO_TEST_SUITE(tokenize_test_suite)

    BOOST_AUTO_TEST_CASE(delimiter_tab) {

        std::stringstream ss;
        ss << "123.123.123.123" << '\t' <<  "99";
        std::vector<std::string> res = {"123.123.123.123", "99"};
        std::vector<std::string> result = tokenize(ss.str(), '\t');
        BOOST_CHECK_EQUAL_COLLECTIONS(res.begin(), res.end(), result.begin(), result.end());
    }

    BOOST_AUTO_TEST_CASE(delimiter_dot) {

        std::vector<std::string> res = {"1", "2", "3", "200"};
        std::vector<std::string> result = tokenize("1.2.3.200", '.');
        BOOST_CHECK_EQUAL_COLLECTIONS(res.begin(), res.end(), result.begin(), result.end());
    }

BOOST_AUTO_TEST_SUITE_END()
