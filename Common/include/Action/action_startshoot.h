#ifndef ACTION_STARTSHOOT_H
#define ACTION_STARTSHOOT_H

#include "action.h"

class StartShootAction : public Action {

public:
    StartShootAction() = default;

    [[nodiscard]] virtual std::vector<int8_t> serialize() const override;

    ~StartShootAction() = default;
};

#endif  // ACTION_STARTSHOOT_H
