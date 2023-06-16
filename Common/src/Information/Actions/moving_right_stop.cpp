//
// Created by luan on 13/06/23.
//
#include "../../../include/Information/Actions/moving_right_stop.h"

std::vector<int8_t> StopMovingRightAction::serialize() const {
    return {ACTION_MOVE, OFF, X, RIGHT, NORMAL};
}

