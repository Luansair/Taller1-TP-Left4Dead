#include "../../../include/Information/Actions/throw_stop.h"
#include "../../../include/Information/information_code.h"

std::vector<std::int8_t> StopThrowAction::serialize() const {
    using std::int8_t;
    return {static_cast<int8_t>(InformationID::ACTION_THROW),
            static_cast<int8_t>(ActionState::OFF)};
}
