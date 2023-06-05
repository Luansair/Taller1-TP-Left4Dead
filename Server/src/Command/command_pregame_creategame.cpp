//
// Created by luan on 03/06/23.
//
#include "../../include/Command/command_pregame_creategame.h"
#include "../../../Common/include/Feedback/feedback_server_creategame.h"

bool CreateGameCommand::execute(GameManager &game_manager,
                                Queue<std::shared_ptr<InGameCommand>> *&game_queue,
                                Queue<std::shared_ptr<ServerFeedback>> &player_queue,
                                std::uint8_t *player_id) {
    // Creates the game and retrieves its code.
    std::uint32_t game_code = game_manager.createGame(game_queue,
                                                      player_queue,
                                                      player_id);
    // Creates the smart pointer for RAII
    std::shared_ptr<CreateGameFeedback> create_feed(
            new CreateGameFeedback(game_code));
    // Push feedback for the player
    player_queue.push(create_feed);
    return true;
}
