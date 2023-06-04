#ifndef ACTION_CREATEGAME_H
#define ACTION_CREATEGAME_H

#include "action.h"

class CreateGameAction : public Action {

public:
    CreateGameAction();

    [[nodiscard]] virtual std::vector<int8_t> serialize() const override;

    ~CreateGameAction() = default;
};

#endif  // ACTION_CREATEGAME_H
