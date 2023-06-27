#include "../../../include/Information/Actions/moving_up_start.h"
#include "../../../include/Information/information_code.h"

std::vector<int8_t> StartMovingUpAction::serialize() const {
    return {ACTION_MOVE, ON, Y, UP, NORMAL};
}
