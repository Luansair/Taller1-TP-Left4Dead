#include "../../../include/Information/Actions/exit_stop.h"
#include "../../../include/Information/information_code.h"

std::vector<std::int8_t> StopExitAction::serialize() const {
    using std::int8_t;
    return {static_cast<int8_t>(InformationID::ACTION_EXIT),
            static_cast<int8_t>(ActionState::OFF)};
}
