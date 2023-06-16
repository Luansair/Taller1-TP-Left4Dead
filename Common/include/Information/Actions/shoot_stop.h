#ifndef ACTION_STOPSHOOT_H
#define ACTION_STOPSHOOT_H

#include "../information.h"

class StopShootAction : public Information {

public:
    StopShootAction() = default;

    [[nodiscard]] virtual std::vector<int8_t> serialize() const override;

    StopShootAction(const StopShootAction&) = delete;
    StopShootAction& operator=(const StopShootAction&) = delete;

    ~StopShootAction() override = default;
};

#endif  // ACTION_STOPSHOOT_H
