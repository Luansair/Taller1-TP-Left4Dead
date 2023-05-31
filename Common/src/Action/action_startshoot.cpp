#include "../../include/Action/action_startshoot.h"
#include "../../include/Action/action_code.h"



std::vector<std::int8_t> StartShootAction::serialize() const {
    using std::int8_t;
    return {static_cast<int8_t>(ActionID::SHOOT), static_cast<int8_t>
    (ActionState::ON)};
}

StartShootAction::StartShootAction() :
    Action(ActionID::SHOOT) {
}
