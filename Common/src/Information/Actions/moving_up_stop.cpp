#include "../../../include/Information/Actions/moving_up_stop.h"

std::vector<int8_t> StopMovingUpAction::serialize() const {
    return {ACTION_MOVE, OFF, Y, UP, NORMAL};
}