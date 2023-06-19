//
// Created by luan on 03/06/23.
//
#include "../../include/Command/command_ingame_startshoot.h"

StartShootCommand::StartShootCommand(std::uint8_t player_id) :
    InGameCommand(player_id) {
}

void StartShootCommand::execute(Match &match) const {
    match.shoot(player_id, ActionState::ON);
}
