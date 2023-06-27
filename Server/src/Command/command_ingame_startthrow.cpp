#include "../../include/Command/command_ingame_startthrow.h"

StartThrowCommand::StartThrowCommand(std::uint8_t player_id) :
    InGameCommand(player_id) {
}

void StartThrowCommand::execute(std::shared_ptr<Match> &match) const {
    match->throwGrenade(player_id, ActionState::ON);
}
