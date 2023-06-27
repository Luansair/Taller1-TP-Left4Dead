#ifndef TP_MOVING_DOWN_STOP_H
#define TP_MOVING_DOWN_STOP_H

#include "../information.h"

class StopMovingDownAction : public Information {
public:
    StopMovingDownAction() = default;

    [[nodiscard]] std::vector<int8_t> serialize() const override;

    StopMovingDownAction(const StopMovingDownAction&) = delete;
    StopMovingDownAction& operator=(const StopMovingDownAction&) = delete;

    ~StopMovingDownAction() override = default;
};

#endif //TP_MOVING_DOWN_STOP_H