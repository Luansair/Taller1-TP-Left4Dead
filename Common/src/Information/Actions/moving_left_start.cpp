//
// Created by luan on 13/06/23.
//
#include "../../../include/Information/Actions/moving_left_start.h"
#include "../../../include/Information/information_code.h"

std::vector<int8_t> StartMovingLeftAction::serialize() const {
    return {ACTION_MOVE, ON, LEFT};
}

