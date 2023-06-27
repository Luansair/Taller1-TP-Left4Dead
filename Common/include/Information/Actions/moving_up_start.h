#ifndef TP_MOVING_UP_START_H
#define TP_MOVING_UP_START_H

#include "../information.h"

class StartMovingUpAction : public Information {
public:
    StartMovingUpAction() = default;

    [[nodiscard]] std::vector<int8_t> serialize() const override;

    StartMovingUpAction(const StartMovingUpAction&) = delete;
    StartMovingUpAction& operator=(const StartMovingUpAction&) = delete;

    ~StartMovingUpAction() override = default;
};


#endif //TP_MOVING_UP_START_H
