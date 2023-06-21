//
// Created by luan on 21/06/23.
//
#include "../../include/Command/command_ingame_pick_soldier.h"

PickSoldierCommand::PickSoldierCommand(std::uint8_t player_id, std::uint8_t soldier_type) :
        InGameCommand(player_id),
        soldier_type(soldier_type) {
}

void PickSoldierCommand::execute(Match &match) const {
    match.join(player_id, soldier_type);
}

