#ifndef TP_COMMAND_INGAME_STARTIDLE_H
#define TP_COMMAND_INGAME_STARTIDLE_H

#include "command_ingame.h"

class StartIdleCommand : public InGameCommand {
public:
    explicit StartIdleCommand(std::uint8_t player_id);

    virtual void execute(std::shared_ptr<Match> &match) const override;

    StartIdleCommand(const StartIdleCommand&) = delete;
    StartIdleCommand& operator=(const StartIdleCommand&) = delete;

    ~StartIdleCommand() override = default;
};

#endif //TP_COMMAND_INGAME_STARTIDLE_H
