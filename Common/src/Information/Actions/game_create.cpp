#include "../../../include/Information/Actions/game_create.h"
#include "../../../include/Information/information_code.h"

std::vector<std::int8_t> CreateGameAction::serialize() const {
    using std::int8_t;
    return {static_cast<int8_t>(InformationID::REQUEST_CREATE_GAME)};
}

