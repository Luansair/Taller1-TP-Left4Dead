#ifndef ACTION_STARTSHOOT_H
#define ACTION_STARTSHOOT_H

#include "../information.h"

class StartShootAction : public Information {

public:
    StartShootAction() = default;

    [[nodiscard]] virtual std::vector<int8_t> serialize() const override;

    StartShootAction(const StartShootAction&) = delete;
    StartShootAction& operator=(const StartShootAction&) = delete;

    ~StartShootAction() override = default;
};

#endif  // ACTION_STARTSHOOT_H
