#include "../../include/Information/action_startshoot.h"
#include "../../include/Information/information_code.h"

std::vector<std::int8_t> StartShootAction::serialize() const {
    using std::int8_t;
    return {static_cast<int8_t>(InformationID::ACTION_SHOOT), static_cast<int8_t>
    (ActionState::ON)};
}
