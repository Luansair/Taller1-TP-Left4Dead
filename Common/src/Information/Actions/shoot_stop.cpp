#include "../../../include/Information/Actions/shoot_stop.h"
#include "../../../include/Information/information_code.h"

std::vector<std::int8_t> StopShootAction::serialize() const {
    using std::int8_t;
    return {static_cast<int8_t>(InformationID::ACTION_SHOOT),
            static_cast<int8_t>(ActionState::OFF)};
}
