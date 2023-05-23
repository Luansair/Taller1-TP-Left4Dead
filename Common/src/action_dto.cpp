#include <sstream>
#include "../include/action_dto.h"
#include "../include/action_code.h"

Action::Action() = default;

StartShootAction::StartShootAction() = default;

std::vector<std::int8_t> StartShootAction::serialize() const {
    using std::int8_t;
    return {static_cast<int8_t>(ActionID::SHOOT), static_cast<int8_t>
    (ActionState::ON)};
}



