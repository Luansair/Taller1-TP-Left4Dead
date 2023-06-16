#ifndef TP_MOVING_UP_STOP_H
#define TP_MOVING_UP_STOP_H

#include "../information.h"

class StopMovingUpAction : public Information {
public:
    StopMovingUpAction() = default;

    [[nodiscard]] std::vector<int8_t> serialize() const override;

    StopMovingUpAction(const StopMovingUpAction&) = delete;
    StopMovingUpAction& operator=(const StopMovingUpAction&) = delete;

    ~StopMovingUpAction() override = default;
};

#endif //TP_MOVING_UP_STOP_H
