#include "../../include/Command/command_ingame_startmove.h"

StartMoveCommand::StartMoveCommand(uint8_t player_id, uint8_t moveAxis, int8_t moveDirection, uint8_t moveForce) :
    InGameCommand(player_id),
    moveAxis(moveAxis),
    moveDirection(moveDirection),
    moveForce(moveForce) {
}

void StartMoveCommand::execute(Match &match) const {
    match.move(player_id, ActionState::ON, moveAxis, moveDirection, moveForce);
}
