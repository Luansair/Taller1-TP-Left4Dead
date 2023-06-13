//
// Created by luan on 13/06/23.
//

#ifndef TP_MOVING_LEFT_STOP_H
#define TP_MOVING_LEFT_STOP_H

#include "../information.h"

class StopMovingLeftAction : public Information {
public:
    StopMovingLeftAction() = default;

    [[nodiscard]] std::vector<int8_t> serialize() const override;

    ~StopMovingLeftAction() override = default;
};

#endif //TP_MOVING_LEFT_STOP_H
