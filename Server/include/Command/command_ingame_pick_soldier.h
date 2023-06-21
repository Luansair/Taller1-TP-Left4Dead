//
// Created by luan on 21/06/23.
//

#ifndef TP_COMMAND_INGAME_PICK_SOLDIER_H
#define TP_COMMAND_INGAME_PICK_SOLDIER_H

#include "command_ingame.h"

class PickSoldierCommand : public InGameCommand {
    std::uint8_t soldier_type;
public:
    explicit PickSoldierCommand(std::uint8_t player_id, std::uint8_t soldier_type);

    void execute(Match& match) const override;

    ~PickSoldierCommand() override = default;
};

#endif //TP_COMMAND_INGAME_PICK_SOLDIER_H
