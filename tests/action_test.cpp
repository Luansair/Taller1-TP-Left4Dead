#include <gtest/gtest.h>
#include "Information/information.h"
#include "Information/information_code.h"
#include "Information/action_startshoot.h"
#include "Information/action_joingame.h"
#include "Information/action_creategame.h"

TEST(actiondto_test, test00ConstructStartShootActionWithCorrectID) {
    auto shoot = StartShootAction();
    ASSERT_EQ(shoot.serialize()[0], InformationID::ACTION_SHOOT);
}

TEST(actiondto_test, test01shootActionNormalCaseSerializationWithPolimorfism) {
    using std::uint8_t;
    using std::vector;

    auto shoot = StartShootAction();
    Information* action = &shoot;

    vector<int8_t> serialized_action = action->serialize();
    ASSERT_EQ(serialized_action[0], InformationID::ACTION_SHOOT);
    ASSERT_EQ(serialized_action[1], ActionState::ON);
}

TEST(actiondto_test,
     JoinTest01JoinActionConstructorWithSerializedJoinShouldDeserializeLittleGameCodeCorrectly) {
    using std::int8_t;
    using std::uint32_t;
    using std::vector;

    uint32_t game_code = 1;
    auto join = JoinGameAction(game_code);
    vector<int8_t> serialized_join = join.serialize();
    auto deserialized_join = JoinGameAction(serialized_join);

    ASSERT_EQ(deserialized_join.game_code, game_code);
}

TEST(actiondto_test,
     JoinTest02JoinActionConstructorWithSerializedJoinShouldDeserializeBigGameCodeCorrectly) {
    using std::int8_t;
    using std::uint32_t;
    using std::vector;

    uint32_t game_code = 16777216;
    auto join = JoinGameAction(game_code);
    vector<int8_t> serialized_join = join.serialize();
    auto deserialized_join = JoinGameAction(serialized_join);

    ASSERT_EQ(deserialized_join.game_code, game_code);
}

TEST(actiondto_test,
     JoinTest03JoinActionConstructorWithSerializedJoinShouldDeserializeRegularGameCodeCorrectly) {
    using std::int8_t;
    using std::uint32_t;
    using std::vector;

    uint32_t game_code = 3456121;
    auto join = JoinGameAction(game_code);
    vector<int8_t> serialized_join = join.serialize();
    auto deserialized_join = JoinGameAction(serialized_join);

    ASSERT_EQ(deserialized_join.game_code, game_code);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}