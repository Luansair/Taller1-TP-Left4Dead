#include <gtest/gtest.h>
#include "../Common/include/action_dto.h"
#include "../Common/include/action_code.h"

TEST(actiondto_test, test00ConstructStartShootActionWithCorrectID) {
    auto shoot = StartShootAction();
    ASSERT_EQ(shoot.serialize()[0], ActionID::SHOOT);
}

TEST(actiondto_test, test01shootActionNormalCaseSerializationWithPolimorfism) {
    using std::uint8_t;
    using std::vector;

    auto shoot = StartShootAction();
    Action* action = &shoot;

    vector<int8_t> serialized_action = action->serialize();
    ASSERT_EQ(serialized_action[0], ActionID::SHOOT);
    ASSERT_EQ(serialized_action[1], ActionState::ON);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}