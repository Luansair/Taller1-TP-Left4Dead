#include <sstream>
#include "../include/action_dto.h"
#include "../include/action_code.h"

std::vector<std::int8_t> StartShootAction::serialize() const {
    using std::int8_t;
    return {static_cast<int8_t>(ActionID::SHOOT), static_cast<int8_t>
    (ActionState::ON)};
}

std::vector<std::int8_t> CreateGameAction::serialize() const {
    using std::int8_t;
    return {static_cast<int8_t>(ActionID::CREATE)};
}

JoinGameAction::JoinGameAction(uint32_t game_code) :
    game_code(game_code) {
}

std::vector<std::int8_t> JoinGameAction::serialize() const {
    using std::int8_t;
    using std::vector;

    vector<int8_t> result;
    result.reserve(5);
    result.push_back(static_cast<int8_t>(ActionID::JOIN));
    for (int i = 0; i < 4; i++) {
        // The mask guarantee that the 8 less significant bits are extracted.
        uint32_t mask = 0xFF;  // 00000000000000000000000011111111
        auto byte = static_cast<int8_t>((game_code >> (i * 8)) & mask);
        result.push_back(byte);
    }
    return result;
    // 40 e2 01 00
}

