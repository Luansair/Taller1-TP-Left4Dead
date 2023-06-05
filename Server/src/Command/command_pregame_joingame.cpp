//
// Created by luan on 03/06/23.
//
#include "../../include/Command/command_pregame_joingame.h"

JoinGameCommand::JoinGameCommand(std::uint32_t game_code) :
    game_code(game_code) {
}

bool JoinGameCommand::execute(GameManager &game_manager,
                              Queue<std::shared_ptr<InGameCommand>> *&game_queue,
                              Queue<std::shared_ptr<ServerFeedback>> &player_queue,
                              std::uint8_t *player_id) {
    return game_manager.joinGame(game_queue, player_queue,
                                 player_id, game_code);
}
