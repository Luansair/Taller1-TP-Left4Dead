#ifndef TP_COMMAND_INGAME_STARTEXIT_H
#define TP_COMMAND_INGAME_STARTEXIT_H

#include "command_ingame.h"

class StartExitCommand : public InGameCommand {
public:
    explicit StartExitCommand(std::uint8_t player_id);

    virtual void execute(std::shared_ptr<Match> &match) const override;

    ~StartExitCommand() = default;
};

#endif //TP_COMMAND_INGAME_STARTEXIT_H
