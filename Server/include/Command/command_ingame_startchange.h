#ifndef TP_COMMAND_INGAME_STARTCHANGE_H
#define TP_COMMAND_INGAME_STARTCHANGE_H

#include "command_ingame.h"

class StartChangeCommand : public InGameCommand {
public:
    explicit StartChangeCommand(std::uint8_t player_id);

    virtual void execute(std::shared_ptr<Match> &match) const override;

    ~StartChangeCommand() = default;
};

#endif //TP_COMMAND_INGAME_STARTCHANGE_H
