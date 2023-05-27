#include <gtest/gtest.h>
#include "game_manager.h"

TEST(gamemanager_test, test00CreateGameShouldChangeGameQueuePointer) {
    Queue<Command*>* game_q = nullptr;
    Queue<GameState*> player_q(10);
    std::uint8_t player_id;
    GameManager manager = GameManager();

    manager.createGame(game_q, player_q, &player_id);
    ASSERT_NE(game_q, nullptr);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
