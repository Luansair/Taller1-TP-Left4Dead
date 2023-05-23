#include <gtest/gtest.h>
#include "../Common/include/action_dto.h"
#include "../Common/include/action_code.h"

TEST(actiondto_test, test00ConstructShootActionWithCorrectID) {
    auto shoot = ShootAction(ActionState::ON);
    ASSERT_EQ(shoot.serialize()[0], ActionID::SHOOT);
}

TEST(actiondto_test, test01shootActionNormalCaseSerializationWithPolimorfism) {
    using std::uint8_t;
    using std::vector;

    auto action_state = ActionState::ON;
    auto shoot = ShootAction(action_state);
    Action* action = &shoot;

    vector<int8_t> serialized_action = action->serialize();
    ASSERT_EQ(serialized_action[0], ActionID::SHOOT);
    ASSERT_EQ(serialized_action[1], action_state);
}

TEST(actiondto_test, test03ConstructsShootActionWithInvalidStateThrows) {
    using std::uint8_t;
    for (uint8_t state = 0; state < 11; state++) {
        if (state != ActionState::ON && state != ActionState::OFF) {
            ASSERT_THROW((ShootAction(state)), std::runtime_error);
        }
    }
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}