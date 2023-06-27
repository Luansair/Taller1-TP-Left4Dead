#ifndef TP_COMMAND_INGAME_STARTREVIVE_H
#define TP_COMMAND_INGAME_STARTREVIVE_H

#include "command_ingame.h"

class StartReviveCommand : public InGameCommand {
public:
    explicit StartReviveCommand(std::uint8_t player_id);

    virtual void execute(std::shared_ptr<Match> &match) const override;

    ~StartReviveCommand() = default;
};

#endif //TP_COMMAND_INGAME_STARTREVIVE_H
