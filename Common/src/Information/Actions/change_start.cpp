#include "../../../include/Information/Actions/change_start.h"
#include "../../../include/Information/information_code.h"

std::vector<std::int8_t> StartChangeAction::serialize() const {
    using std::int8_t;
    return {static_cast<int8_t>(InformationID::ACTION_CHANGE),
            static_cast<int8_t>(ActionState::ON)};
}