#include "../../include/Command/command_ingame_startrevive.h"

StartReviveCommand::StartReviveCommand(std::uint8_t player_id) :
    InGameCommand(player_id) {
}

void StartReviveCommand::execute(std::shared_ptr<Match> &match) const {
    match->revive(player_id, ActionState::ON);
}
