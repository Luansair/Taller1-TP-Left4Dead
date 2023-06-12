#include "../../include/Command/command_ingame_startreload.h"

StartReloadCommand::StartReloadCommand(std::uint8_t player_id) :
    InGameCommand(player_id) {
}

void StartReloadCommand::execute(Match &match) const {
    match.reload(player_id, ActionState::ON);
}
