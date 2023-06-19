#include "../../../include/Information/Actions/revive_stop.h"
#include "../../../include/Information/information_code.h"

std::vector<std::int8_t> StopReviveAction::serialize() const {
    using std::int8_t;
    return {static_cast<int8_t>(InformationID::ACTION_REVIVE),
            static_cast<int8_t>(ActionState::OFF)};
}
