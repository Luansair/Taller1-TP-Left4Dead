#ifndef TP_COMMAND_INGAME_STOPTHROW_H
#define TP_COMMAND_INGAME_STOPTHROW_H

#include "command_ingame.h"

class StopThrowCommand : public InGameCommand {
public:
    explicit StopThrowCommand(std::uint8_t player_id);

    virtual void execute(std::shared_ptr<Match> &match) const override;

    ~StopThrowCommand() = default;
};

#endif //TP_COMMAND_INGAME_STOPTHROW_H
