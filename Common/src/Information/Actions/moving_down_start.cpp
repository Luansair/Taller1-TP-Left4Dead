#include "../../../include/Information/Actions/moving_down_start.h"
#include "../../../include/Information/information_code.h"

std::vector<int8_t> StartMovingDownAction::serialize() const {
    return {ACTION_MOVE, ON, Y, DOWN, NORMAL};
}
