#ifndef GAME_MANAGER_H_
#define GAME_MANAGER_H_

#include <vector>
#include "game.h"

class GameManager {
    std::vector<Game> games;
    std::hash<int> game_codes;

    /*
     * Uses a hash to retreive an index to find a 'game' from 'games' vector.
     * The parameter 'game_code' is the key to the index.
     * Since 'game_code' is randomly generated a hash is needed for
     * performance.
     * Example: game_code 1203194 -> 0 (it is the id of the first game created)
     */
    int getGameIndex(int game_code);

public:
    /*
     * It could receive a 'seed' parameter to generate the random numbers.
     */
    GameManager() = default;
};

#endif  // GAME_MANAGER_H_
