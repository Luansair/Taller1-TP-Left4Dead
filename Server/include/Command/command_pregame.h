//
// Created by luan on 03/06/23.
//

#ifndef TP_COMMAND_PREGAME_H
#define TP_COMMAND_PREGAME_H

#include "command_ingame.h"
#include "../../../libs/queue.h"
#include "../game_state.h"
#include "../game_manager.h"

class PreGameCommand {

public:
    PreGameCommand() = default;

    virtual bool execute(GameManager& game_manager,
                         Queue<InGameCommand *> *&game_queue,
                         Queue<GameState *> &player_queue,
                         std::uint8_t* player_id) = 0;

    virtual ~PreGameCommand() = default;
};

#endif //TP_COMMAND_PREGAME_H
