//
// Created by luan on 13/06/23.
//
#include "../../../include/Information/Actions/moving_right_start.h"
#include "../../../include/Information/information_code.h"

std::vector<int8_t> StartMovingRightAction::serialize() const {
    return {ACTION_MOVE, ON, X, RIGHT, NORMAL};
}

