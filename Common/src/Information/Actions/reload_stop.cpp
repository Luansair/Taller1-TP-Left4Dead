#include "../../../include/Information/Actions/reload_stop.h"
#include "../../../include/Information/information_code.h"

std::vector<std::int8_t> StopReloadAction::serialize() const {
    using std::int8_t;
    return {static_cast<int8_t>(InformationID::ACTION_RELOAD),
            static_cast<int8_t>(ActionState::OFF)};
}
