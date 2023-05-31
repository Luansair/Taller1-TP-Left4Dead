#include "action.h"

#ifndef ACTION_CREATEGAME_H
#define ACTION_CREATEGAME_H

class CreateGameAction : public Action {

public:
    CreateGameAction();
    [[nodiscard]] virtual std::vector<int8_t> serialize() const override;

    ~CreateGameAction() override = default;
};

#endif  // ACTION_CREATEGAME_H
