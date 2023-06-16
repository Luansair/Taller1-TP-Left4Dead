#include "../../../include/Information/Actions/moving_down_stop.h"

std::vector<int8_t> StopMovingDownAction::serialize() const {
    return {ACTION_MOVE, OFF, Y, DOWN, NORMAL};
}