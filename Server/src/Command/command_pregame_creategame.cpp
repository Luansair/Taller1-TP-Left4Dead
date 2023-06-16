//
// Created by luan on 03/06/23.
//
#include "../../include/Command/command_pregame_creategame.h"
#include "../../../Common/include/Information/feedback_server_creategame.h"

bool CreateGameCommand::execute(GameManager &game_manager,
                                Queue<std::shared_ptr<InGameCommand>> *&game_queue,
                                const std::shared_ptr<Queue<std::shared_ptr<Information>>> &player_queue,
                                std::uint8_t *player_id) {
    // Creates the game.
    game_manager.createGame(game_queue,
                            player_queue,
                            player_id);
    return true;
}
