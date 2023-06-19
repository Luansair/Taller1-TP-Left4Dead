#include "../../include/Command/command_ingame_stoprevive.h"

StopReviveCommand::StopReviveCommand(std::uint8_t player_id) :
    InGameCommand(player_id) {
}

void StopReviveCommand::execute(Match &match) const {
    match.revive(player_id, ActionState::OFF);
}
