#ifndef TP_MOVING_DOWN_START_H
#define TP_MOVING_DOWN_START_H

#include "../information.h"

class StartMovingDownAction : public Information {
public:
    StartMovingDownAction() = default;

    [[nodiscard]] std::vector<int8_t> serialize() const override;

    StartMovingDownAction(const StartMovingDownAction&) = delete;
    StartMovingDownAction& operator=(const StartMovingDownAction&) = delete;

    ~StartMovingDownAction() override = default;
};


#endif //TP_MOVING_DOWN_START_H
