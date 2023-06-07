#include <gtest/gtest.h>
#include "Information/information.h"
#include "Information/information_code.h"
#include "Information/action_startshoot.h"
#include "Information/action_joingame.h"
#include "Information/action_creategame.h"
#include "Information/state_dto_element.h"
#include "Information/feedback_server_gamestate.h"

enum JoinGameVector : std::uint8_t {
    JOIN_GAME_ID,
    BYTE_1,
    BYTE_2,
    BYTE_3,
    BYTE_4
};


TEST(information_test, test00ConstructStartShootActionWithCorrectID) {
    auto shoot = StartShootAction();
    ASSERT_EQ(shoot.serialize()[0], InformationID::ACTION_SHOOT);
}

TEST(information_test, test01shootActionNormalCaseSerializationWithPolimorfism) {
    using std::uint8_t;
    using std::vector;

    auto shoot = StartShootAction();
    Information* action = &shoot;

    vector<int8_t> serialized_action = action->serialize();
    ASSERT_EQ(serialized_action[0], InformationID::ACTION_SHOOT);
    ASSERT_EQ(serialized_action[1], ActionState::ON);
}

TEST(information_test,
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

TEST(information_test,
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

TEST(information_test,
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

TEST(informatio_test,
     JoinTestSerialize00EachGameCodeByteShouldBeSerializedInBigEndian) {
    using std::int8_t;
    using std::uint32_t;
    using std::vector;

    uint32_t game_code = 0x12345678;

    auto join = JoinGameAction(game_code);
    vector<int8_t> serialized_join = join.serialize();

    EXPECT_EQ(serialized_join[JOIN_GAME_ID], InformationID::REQUEST_JOIN_GAME);
    EXPECT_EQ(serialized_join[BYTE_1], 0x12);
    EXPECT_EQ(serialized_join[BYTE_2], 0x34);
    EXPECT_EQ(serialized_join[BYTE_3], 0x56);
    EXPECT_EQ(serialized_join[BYTE_4], 0x78);
}

TEST(information_test,
     GameStateSerialize00EachByteOfActorIDShouldBeSerializedProperly) {
    using std::uint8_t;
    using std::uint16_t;
    using std::size_t;
    using std::vector;
    using std::pair;

    vector<pair<uint16_t, ElementStateDTO>> actors;
    uint16_t actor_id = 0x1234;
    ElementStateDTO actor_state = {SOLDIER_1, SOLDIER_1_ATTACK, DRAW_RIGHT,
                                   0x12345678, 0x11223344};
    actors.emplace_back(actor_id, actor_state);
    GameStateFeedback game_state = GameStateFeedback(std::move(actors));

    vector<int8_t> serialized_game_state = game_state.serialize();

    EXPECT_EQ(serialized_game_state.at(0), InformationID::FEEDBACK_GAME_STATE);
    EXPECT_EQ(serialized_game_state.at(1), 0x00);
    EXPECT_EQ(serialized_game_state.at(2), 0x00);
    EXPECT_EQ(serialized_game_state.at(3), 0x00);
    EXPECT_EQ(serialized_game_state.at(4), 0x01);
    EXPECT_EQ(serialized_game_state.at(5), 0x12);
    EXPECT_EQ(serialized_game_state.at(6), 0x34);
    EXPECT_EQ(serialized_game_state.at(7), SOLDIER_1);
    EXPECT_EQ(serialized_game_state.at(8), SOLDIER_1_ATTACK);
    EXPECT_EQ(serialized_game_state.at(9), DRAW_RIGHT);
    EXPECT_EQ(serialized_game_state.at(10), 0x12);
    EXPECT_EQ(serialized_game_state.at(11), 0x34);
    EXPECT_EQ(serialized_game_state.at(12), 0x56);
    EXPECT_EQ(serialized_game_state.at(13), 0x78);
    EXPECT_EQ(serialized_game_state.at(14), 0x11);
    EXPECT_EQ(serialized_game_state.at(15), 0x22);
    EXPECT_EQ(serialized_game_state.at(16), 0x33);
    EXPECT_EQ(serialized_game_state.at(17), 0x44);
    // Me da fiaca, ademas el tamaño depende del SO (4 u 8 bytes)
    // Capaz conviene usar para todos los valores grandes std::uint32_t
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}