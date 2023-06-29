#include "../../include/Command/command_ingame_startexit.h"

StartExitCommand::StartExitCommand(std::uint8_t player_id) :
    InGameCommand(player_id) {
}

void StartExitCommand::execute(std::shared_ptr<Match> &match) const {
    match->killActor(player_id, ActionState::ON);
}
