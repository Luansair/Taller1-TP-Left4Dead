#include "../../include/Command/command_ingame_startidle.h"

StartIdleCommand::StartIdleCommand(std::uint8_t player_id) :
    InGameCommand(player_id) {
}

void StartIdleCommand::execute(Match &match) const {
    match.idle(player_id, ActionState::ON);
}
