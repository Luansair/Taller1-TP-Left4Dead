#include "../../include/Command/command_ingame_startchange.h"

StartChangeCommand::StartChangeCommand(std::uint8_t player_id) :
    InGameCommand(player_id) {
}

void StartChangeCommand::execute(std::shared_ptr<Match> &match) const {
    match->change_grenade(player_id, ActionState::ON);
}