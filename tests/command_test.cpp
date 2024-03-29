//
// Created by luan on 04/06/23.
//
#include <gtest/gtest.h>

#include "game_manager.h"
#include "Command/command_ingame_startshoot.h"
#include "Command/command_pregame_creategame.h"

TEST(command_test,
     CreateGameTest00ExecuteShouldReturnTrue) {
    Queue<std::shared_ptr<InGameCommand>>* game_q = nullptr;
    std::shared_ptr<Queue<std::shared_ptr<Information>>> player_q =
            std::make_shared<Queue<std::shared_ptr<Information>>>(10000);
    std::uint8_t player_id = 0;
    GameManager manager = GameManager();
    CreateGameCommand create_game_cmd{REQUEST_SURVIVAL, REQUEST_EASY};

    bool joined = create_game_cmd.execute(manager, game_q, player_q,
                                          &player_id);

    ASSERT_TRUE(joined);
}

TEST(command_test,
     CreateGameTest01ExecuteShouldSetUpPlayerIDDifferentFromZero) {
    Queue<std::shared_ptr<InGameCommand>>* game_q = nullptr;
    std::shared_ptr<Queue<std::shared_ptr<Information>>> player_q =
            std::make_shared<Queue<std::shared_ptr<Information>>>(10000);
    std::uint8_t player_id = 0;
    GameManager manager = GameManager();
    CreateGameCommand create_game_cmd{REQUEST_SURVIVAL, REQUEST_EASY};

    create_game_cmd.execute(manager, game_q, player_q,
                                          &player_id);

    ASSERT_NE(player_id, 0);
}

TEST(command_test,
     CreateGameTest02ExecuteShouldSetUpGameQueueDifferentFromNull) {
    Queue<std::shared_ptr<InGameCommand>>* game_q = nullptr;
    std::shared_ptr<Queue<std::shared_ptr<Information>>> player_q =
            std::make_shared<Queue<std::shared_ptr<Information>>>(10000);
    std::uint8_t player_id = 0;
    GameManager manager = GameManager();
    CreateGameCommand create_game_cmd{REQUEST_SURVIVAL, REQUEST_EASY};

    create_game_cmd.execute(manager, game_q, player_q,
                            &player_id);

    ASSERT_NE(game_q, nullptr);
}

TEST(command_test,
     CreateGameTest03ExecuteThenCallingPushToPlayerQueueShouldNotBreak) {
    Queue<std::shared_ptr<InGameCommand>>* game_q = nullptr;
    std::shared_ptr<Queue<std::shared_ptr<Information>>> player_q =
            std::make_shared<Queue<std::shared_ptr<Information>>>(10000);
    std::uint8_t player_id = 0;
    GameManager manager = GameManager();
    CreateGameCommand create_game_cmd{REQUEST_SURVIVAL, REQUEST_EASY};

    create_game_cmd.execute(manager, game_q, player_q,
                            &player_id);

    ASSERT_NO_FATAL_FAILURE(player_q->push(nullptr));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}