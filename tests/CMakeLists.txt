include(FetchContent)

FETCHCONTENT_DECLARE(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1)

FETCHCONTENT_MAKEAVAILABLE(googletest)
add_library(GTest::Gtest INTERFACE IMPORTED)
target_link_libraries(GTest::Gtest INTERFACE gtest_main)

include_directories(${PROJECT_SOURCE_DIR}/Common/include)

add_executable(resolver_test resolver_test.cpp
        ${PROJECT_SOURCE_DIR}/Common/src/resolver.cpp)

find_package(GTest REQUIRED)

target_link_libraries(resolver_test
        PRIVATE
        GTest::GTest)

add_test(resolver_gtests resolver_test)