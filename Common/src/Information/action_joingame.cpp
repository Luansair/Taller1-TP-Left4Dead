#include "../../include/Information/action_joingame.h"
#include "../../include/Information/information_code.h"

JoinGameAction::JoinGameAction(uint32_t game_code) :
        game_code(game_code) {
}

JoinGameAction::JoinGameAction(
        const std::vector<int8_t>& serialized_bigendian_game_code) :
        game_code(deserializeFourBytesNumber
        (serialized_bigendian_game_code)) {
}

std::vector<std::int8_t> JoinGameAction::serialize() const {
    using std::int8_t;
    using std::vector;
    using std::uint32_t;

    vector<int8_t> result;
    result.reserve(5);

    result.push_back(static_cast<int8_t>(InformationID::REQUEST_JOIN_GAME));
    this->serializeNumber<uint32_t>(result, game_code);
    return result;
}
