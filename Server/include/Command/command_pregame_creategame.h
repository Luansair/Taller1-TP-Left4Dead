//
// Created by luan on 03/06/23.
//

#ifndef TP_COMMAND_PREGAME_CREATEGAME_H
#define TP_COMMAND_PREGAME_CREATEGAME_H

#include "command_pregame.h"

class CreateGameCommand : public PreGameCommand {
public:
    CreateGameCommand() = default;

    virtual bool execute(GameManager& game_manager,
                         Queue<InGameCommand *> *&game_queue,
                         Queue<GameState *> &player_queue,
                         std::uint8_t* player_id) override;

    ~CreateGameCommand() = default;
};


#endif //TP_COMMAND_PREGAME_CREATEGAME_H
