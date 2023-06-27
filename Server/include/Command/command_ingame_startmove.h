#ifndef TP_COMMAND_INGAME_STARTMOVE_H
#define TP_COMMAND_INGAME_STARTMOVE_H

#include "command_ingame.h"

class StartMoveCommand : public InGameCommand {
public:
    uint8_t moveAxis;
    int8_t moveDirection;
    uint8_t moveForce;
    explicit StartMoveCommand(uint8_t soldier_id, uint8_t moveAxis, int8_t moveDirection, uint8_t moveForce);

    virtual void execute(std::shared_ptr<Match> &match) const override;

    StartMoveCommand(const StartMoveCommand&) = delete;
    StartMoveCommand& operator=(const StartMoveCommand&) = delete;

    ~StartMoveCommand() override = default;
};

#endif //TP_COMMAND_INGAME_STARTMOVE_H
