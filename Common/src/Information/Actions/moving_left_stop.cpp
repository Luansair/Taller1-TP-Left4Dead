//
// Created by luan on 13/06/23.
//
#include "../../../include/Information/Actions/moving_left_stop.h"

std::vector<int8_t> StopMovingLeftAction::serialize() const {
    return {ACTION_MOVE, OFF, LEFT};
}

