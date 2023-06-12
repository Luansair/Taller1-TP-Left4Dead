#ifndef TP_COMMAND_INGAME_STARTIDLE_H
#define TP_COMMAND_INGAME_STARTIDLE_H

#include "command_ingame.h"

class StartIdleCommand : public InGameCommand {
public:
    explicit StartIdleCommand(std::uint8_t player_id);

    virtual void execute(Match& match) const override;

    ~StartIdleCommand() = default;
};

#endif //TP_COMMAND_INGAME_STARTIDLE_H
