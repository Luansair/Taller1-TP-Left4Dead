#ifndef TP_COMMAND_INGAME_STARTTHROW_H
#define TP_COMMAND_INGAME_STARTTHROW_H

#include "command_ingame.h"

class StartThrowCommand : public InGameCommand {
public:
    explicit StartThrowCommand(std::uint8_t player_id);

    virtual void execute(std::shared_ptr<Match> &match) const override;

    ~StartThrowCommand() = default;
};

#endif //TP_COMMAND_INGAME_STARTTHROW_H
