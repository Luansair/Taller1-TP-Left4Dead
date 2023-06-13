//
// Created by luan on 13/06/23.
//

#ifndef TP_MOVING_RIGHT_START_H
#define TP_MOVING_RIGHT_START_H

#include "../information.h"

class StartMovingRightAction : public Information {

public:
    StartMovingRightAction() = default;

    [[nodiscard]] std::vector<int8_t> serialize() const override;

    ~StartMovingRightAction() override = default;
};

#endif //TP_MOVING_RIGHT_START_H
