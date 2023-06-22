//
// Created by luan on 03/06/23.
//

#ifndef TP_COMMAND_PREGAME_CREATEGAME_H
#define TP_COMMAND_PREGAME_CREATEGAME_H

#include "command_pregame.h"
#include <cstdint>

class CreateGameCommand : public PreGameCommand {
    std::uint8_t gameMode;
    std::uint8_t gameDifficulty;
public:
    explicit CreateGameCommand(std::uint8_t gameMode, std::uint8_t gameDifficulty);

    virtual bool execute(GameManager& game_manager,
                         Queue<std::shared_ptr<InGameCommand>> *&game_queue,
                         const std::shared_ptr<Queue<std::shared_ptr<Information>>> &player_queue,
                         std::uint8_t* player_id) override;

    ~CreateGameCommand() = default;
};


#endif //TP_COMMAND_PREGAME_CREATEGAME_H
