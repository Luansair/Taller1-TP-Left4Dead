#include "action.h"

#ifndef ACTION_STARTSHOOT_H
#define ACTION_STARTSHOOT_H

class StartShootAction : public Action {

public:
    StartShootAction();
    [[nodiscard]] virtual std::vector<int8_t> serialize() const override;

    ~StartShootAction() override = default;
};

#endif  // ACTION_STARTSHOOT_H
