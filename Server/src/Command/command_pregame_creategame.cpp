//
// Created by luan on 03/06/23.
//
#include "../../include/Command/command_pregame_creategame.h"

bool CreateGameCommand::execute(GameManager &game_manager,
                                Queue<InGameCommand *> *&game_queue,
                                Queue<GameState *> &player_queue,
                                std::uint8_t *player_id) {
    game_manager.createGame(game_queue,
                            player_queue,
                            player_id);
    return true;
}
