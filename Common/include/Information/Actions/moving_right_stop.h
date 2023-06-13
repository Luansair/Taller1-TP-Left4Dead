//
// Created by luan on 13/06/23.
//

#ifndef TP_MOVING_RIGHT_STOP_H
#define TP_MOVING_RIGHT_STOP_H

#include "../information.h"

class StopMovingRightAction : public Information {
public:
    StopMovingRightAction() = default;

    [[nodiscard]] std::vector<int8_t> serialize() const override;

    ~StopMovingRightAction() override = default;
};
#endif //TP_MOVING_RIGHT_STOP_H
