//
// Created by luan on 03/06/23.
//

#ifndef TP_COMMAND_PREGAME_JOINGAME_H
#define TP_COMMAND_PREGAME_JOINGAME_H

#include "command_pregame.h"

class JoinGameCommand : public PreGameCommand {
    std::uint32_t game_code;
public:
    explicit JoinGameCommand(std::uint32_t game_code);

    virtual bool execute(GameManager& game_manager,
                         Queue<std::shared_ptr<InGameCommand>> *&game_queue,
                         Queue<std::shared_ptr<Information>> &player_queue,
                         std::uint8_t* player_id) override;

    ~JoinGameCommand() = default;
};


#endif //TP_COMMAND_PREGAME_JOINGAME_H
