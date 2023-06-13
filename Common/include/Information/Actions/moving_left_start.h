//
// Created by luan on 13/06/23.
//

#ifndef TP_MOVING_LEFT_START_H
#define TP_MOVING_LEFT_START_H

#include "../information.h"

class StartMovingLeftAction : public Information {
public:
    StartMovingLeftAction() = default;

    [[nodiscard]] std::vector<int8_t> serialize() const override;

    ~StartMovingLeftAction() override = default;
};


#endif //TP_MOVING_LEFT_START_H
