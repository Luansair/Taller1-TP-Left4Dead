#include <gtest/gtest.h>
#include "../Common/include/resolver.h"

TEST(ResolverTest, ResolvingInvalidAddrThrowsException) {
    const char* invalid_hostname = "invalid hostname";
    const char* invalid_servname = "invalid servname";
    ASSERT_THROW(Resolver(invalid_hostname, invalid_servname, false),
                 std::runtime_error);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}