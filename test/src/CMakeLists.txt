cmake_minimum_required(VERSION 3.2)

project(ip_filter_test)

add_executable(test_ip_filter test_ip_filter.cpp)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

set_target_properties(test_ip_filter PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wall;-Wextra"
        )

set_target_properties(test_ip_filter PROPERTIES
        COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
        INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
        )

target_link_libraries(test_ip_filter ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} ip_address_lib tool_dir)

add_test(${PROJECT_NAME}_executable test_ip_filter)
