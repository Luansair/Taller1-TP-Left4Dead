#include "../../../include/Information/Actions/revive_start.h"
#include "../../../include/Information/information_code.h"

std::vector<std::int8_t> StartReviveAction::serialize() const {
    using std::int8_t;
    return {static_cast<int8_t>(InformationID::ACTION_REVIVE),
            static_cast<int8_t>(ActionState::ON)};
}
