#ifndef TP_COMMAND_INGAME_STARTMOVE_H
#define TP_COMMAND_INGAME_STARTMOVE_H

#include "command_ingame.h"

class StartMoveCommand : public InGameCommand {
public:
    uint8_t moveAxis;
    int8_t moveDirection;
    uint8_t moveForce;
    explicit StartMoveCommand(uint8_t soldier_id, uint8_t moveAxis, int8_t moveDirection, uint8_t moveForce);

    virtual void execute(Match& match) const override;

    ~StartMoveCommand() = default;
};

#endif //TP_COMMAND_INGAME_STARTMOVE_H
