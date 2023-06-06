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
                         Queue<std::shared_ptr<InGameCommand>> *&game_queue,
                         Queue<std::shared_ptr<Information>> &player_queue,
                         std::uint8_t* player_id) override;

    ~CreateGameCommand() = default;
};


#endif //TP_COMMAND_PREGAME_CREATEGAME_H
