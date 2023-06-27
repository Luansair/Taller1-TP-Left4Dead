//
// Created by luan on 03/06/23.
//

#ifndef TP_COMMAND_INGAME_H
#define TP_COMMAND_INGAME_H

#include <cstdint>

#include "../../include/GameLogic/match.h"

class InGameCommand {
protected:
    std::uint8_t player_id;
public:
    explicit InGameCommand(std::uint8_t player_id);

    virtual void execute(std::shared_ptr<Match> &match) const = 0;

    InGameCommand(InGameCommand&&) = default;
    InGameCommand& operator=(InGameCommand&&) = default;

    InGameCommand(const InGameCommand&) = delete;
    InGameCommand& operator=(const InGameCommand&) = delete;

    virtual ~InGameCommand() = default;
};
#endif //TP_COMMAND_INGAME_H
