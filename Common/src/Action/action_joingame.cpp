#include <netinet/in.h>
#include "../../include/Action/action_joingame.h"
#include "../../include/Action/action_code.h"

JoinGameAction::JoinGameAction(uint32_t game_code) :
        Action(ActionID::JOIN),
        game_code(game_code) {
}

JoinGameAction::JoinGameAction(
        const std::vector<int8_t>& serialized_bigendian_game_code) :
        Action(ActionID::JOIN),
        game_code(deserializeFourBytesNumber
        (serialized_bigendian_game_code)) {
}

std::vector<std::int8_t> JoinGameAction::serialize() const {
    using std::int8_t;
    using std::vector;

    vector<int8_t> result;
    result.reserve(5);

    result.push_back(static_cast<int8_t>(ActionID::JOIN));
    serializeFourBytesNumber(result, game_code);
    return result;
}
