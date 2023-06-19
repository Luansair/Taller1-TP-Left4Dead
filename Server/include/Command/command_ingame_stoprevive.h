#ifndef TP_COMMAND_INGAME_STOPREVIVE_H
#define TP_COMMAND_INGAME_STOPREVIVE_H

#include "command_ingame.h"

class StopReviveCommand : public InGameCommand {
public:
    explicit StopReviveCommand(std::uint8_t player_id);

    virtual void execute(Match& match) const override;

    ~StopReviveCommand() = default;
};

#endif //TP_COMMAND_INGAME_STOPREVIVE_H
