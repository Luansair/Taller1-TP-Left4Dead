#ifndef GAME_MANAGER_H_
#define GAME_MANAGER_H_

#include <vector>
#include <map>
#include "game.h"
#include "command.h"
#include "game_state.h"

class GameManager {
    std::map<std::uint32_t,Game*> games;

    [[nodiscard]] std::uint32_t generateGameCode();
public:
    explicit GameManager();

    [[nodiscard]] std::uint32_t createGame(Queue<Command>*& game_queue,
                                           Queue<GameState>*& player_queue,
                                           std::uint8_t* player_id);

    [[nodiscard]] bool joinGame(Queue<Command>*& game_queue,
                                Queue<GameState>*& player_queue,
                                std::uint8_t* player_id,
                                std::uint32_t game_code);

    ~GameManager() = default;
};

#endif  // GAME_MANAGER_H_
