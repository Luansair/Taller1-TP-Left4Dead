#include "../../include/Action/action_creategame.h"
#include "../../include/Action/action_code.h"

std::vector<std::int8_t> CreateGameAction::serialize() const {
    using std::int8_t;
    return {static_cast<int8_t>(ActionID::CREATE)};
}

CreateGameAction::CreateGameAction() :
    Action(ActionID::CREATE) {
}
