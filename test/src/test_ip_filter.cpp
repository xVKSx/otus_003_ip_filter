#define BOOST_TEST_MODULE hello_wolrd_test

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(helloworld_test_suite)

    BOOST_AUTO_TEST_CASE(init_test) {
        BOOST_CHECK(true == true);
    }

BOOST_AUTO_TEST_SUITE_END()
