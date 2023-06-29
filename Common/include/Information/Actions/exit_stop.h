#ifndef ACTION_STOPEXIT_H
#define ACTION_STOPEXIT_H

#include "../information.h"

class StopExitAction : public Information {

public:
    StopExitAction() = default;

    [[nodiscard]] virtual std::vector<int8_t> serialize() const override;

    StopExitAction(const StopExitAction&) = delete;
    StopExitAction& operator=(const StopExitAction&) = delete;

    ~StopExitAction() override = default;
};

#endif  // ACTION_STOPEXIT_H