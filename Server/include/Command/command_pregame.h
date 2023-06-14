//
// Created by luan on 03/06/23.
//

#ifndef TP_COMMAND_PREGAME_H
#define TP_COMMAND_PREGAME_H

#include "command_ingame.h"
#include "../../../libs/queue.h"
#include "../../../Common/include/Information/information.h"
#include "../game_manager.h"

class PreGameCommand {

public:
    PreGameCommand() = default;

    virtual bool execute(GameManager& game_manager,
                         Queue<std::shared_ptr<InGameCommand>> *&game_queue,
                         Queue<std::shared_ptr<Information>> &player_queue,
                         std::uint8_t* player_id) = 0;

    PreGameCommand(PreGameCommand&&) = default;
    PreGameCommand& operator=(PreGameCommand&&) = default;

    PreGameCommand(const PreGameCommand&) = delete;
    PreGameCommand& operator=(const PreGameCommand&) = delete;

    virtual ~PreGameCommand() = default;
};

#endif //TP_COMMAND_PREGAME_H
