//
// Created by luan on 03/06/23.
//

#ifndef TP_COMMAND_INGAME_STARTSHOOT_H
#define TP_COMMAND_INGAME_STARTSHOOT_H

#include "command_ingame.h"

class StartShootCommand : public InGameCommand {
public:
    explicit StartShootCommand(std::uint8_t player_id);

    virtual void execute(Match& match) const override;

    ~StartShootCommand() = default;
};

#endif //TP_COMMAND_INGAME_STARTSHOOT_H
