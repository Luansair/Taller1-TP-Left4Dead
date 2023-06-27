#ifndef ACTION_THROWSHOOT_H
#define ACTION_THROWSHOOT_H

#include "../information.h"

class StartThrowAction : public Information {

public:
    StartThrowAction() = default;

    [[nodiscard]] virtual std::vector<int8_t> serialize() const override;

    StartThrowAction(const StartThrowAction&) = delete;
    StartThrowAction& operator=(const StartThrowAction&) = delete;

    ~StartThrowAction() override = default;
};

#endif  // ACTION_THROWSHOOT_H
