#ifndef GAME_MANAGER_H_
#define GAME_MANAGER_H_

#include <vector>
#include <map>
#include "game.h"
#include "Command/command.h"
#include "GameLogic/match.h"
#include "game_state.h"

class GameManager {
    std::map<std::uint32_t,Game*> games;
    std::mutex mtx;

    [[nodiscard]] std::uint32_t generateGameCode();

    void cleanEmptyGames();
    void cleanAllGames();
public:
    explicit GameManager();

    std::uint32_t createGame(Queue<Command *> *&game_queue,
                             Queue<GameState *> &player_queue,
                             std::uint8_t* player_id);

    bool joinGame(Queue<Command *> *&game_queue,
                  Queue<GameState *> &player_queue,
                  std::uint8_t* player_id,
                  std::uint32_t game_code);

    ~GameManager();
};

#endif  // GAME_MANAGER_H_
