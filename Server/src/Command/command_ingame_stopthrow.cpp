#include "../../include/Command/command_ingame_stopthrow.h"

StopThrowCommand::StopThrowCommand(std::uint8_t player_id) :
    InGameCommand(player_id) {
}

void StopThrowCommand::execute(std::shared_ptr<Match> &match) const {
    match->throwGrenade(player_id, ActionState::OFF);
}
