#include "../../../include/Information/Actions/game_create.h"
#include "../../../include/Information/information_code.h"

CreateGameAction::CreateGameAction(uint8_t mode, uint8_t dif) : 
    gameMode(mode),
    difficulty(dif) {}

std::vector<std::int8_t> CreateGameAction::serialize() const {
    using std::int8_t;
    return {REQUEST_CREATE_GAME, static_cast<int8_t>(gameMode), static_cast<int8_t>(difficulty)};
}

