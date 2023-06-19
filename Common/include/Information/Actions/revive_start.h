#ifndef ACTION_STARTREVIVE_H
#define ACTION_STARTREVIVE_H

#include "../information.h"

class StartReviveAction : public Information {

public:
    StartReviveAction() = default;

    [[nodiscard]] virtual std::vector<int8_t> serialize() const override;

    StartReviveAction(const StartReviveAction&) = delete;
    StartReviveAction& operator=(const StartReviveAction&) = delete;

    ~StartReviveAction() override = default;
};

#endif  // ACTION_STARTREVIVE_H
