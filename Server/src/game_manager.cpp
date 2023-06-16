#include <random>
#include "../include/game_manager.h"
#include "../../Common/include/Information/feedback_server_creategame.h"

/*
 * MAX_SIZE is defined so the chances for the generator to generate a game_code
 * that already exists is too low. This way the game code generator doesn't
 * spend too much time searching for a code.
 * It could be improved in the future to avoid using this limit.
 */
constexpr unsigned int MAX_SIZE = 10000;
constexpr std::uint8_t MAX_PLAYERS = 10;


//-----------------------PRIVATE----------------------------//
std::uint32_t GameManager::generateGameCode() {
    using std::random_device;
    using std::mt19937;
    using std::uniform_int_distribution;
    using std::uint32_t;

    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<uint32_t> dist(1000000, 9999999);
    uint32_t game_code;
    // Makes sure to pick an unused game_code.
    do {
        game_code = dist(mt);
    } while (games.find(game_code) != games.end());
    return game_code;
}

void GameManager::cleanEmptyGames() {
    for (auto game = games.begin(); game != games.end(); ) {
        if (game->second->isEmpty()) {
            game->second->stop();
            game->second->Thread::join();
            delete game->second;
            game = games.erase(game);
        } else {
            ++game;
        }
    }
}

void GameManager::cleanAllGames() {
    for (auto & game : games) {
        game.second->stop();
        game.second->Thread::join();
        delete game.second;
    }
}

//-----------------------PUBLIC----------------------------//
GameManager::GameManager() :
        games() {
}

std::uint32_t GameManager::createGame(Queue<std::shared_ptr<InGameCommand>> *&game_queue,
                                      const std::shared_ptr<Queue<std::shared_ptr<Information>>> &player_queue,
                                      std::uint8_t *player_id) {
    using std::uint32_t;
    using std::runtime_error;
    using std::pair;

    using std::shared_ptr;
    using std::make_shared;

    using std::unique_lock;
    using std::mutex;
    /*
     * It could search for empty games to reutilize them. The problem is
     * that it uses the same game_code and is not very secure (old players
     * could re-enter).
     *
     */
    unique_lock<mutex> lck(mtx);
    if (games.size() >= MAX_SIZE) {
        /*
         * Could use a specific type of Exception to avoid stopping the User for
         * joining other game for example, or wait for a game to finish.
         * This will stop the Receiver and therefore the Client from
         * communicating with the Server.
         */
        throw runtime_error("Maximum games capacity reached.\n");
    }

    std::uint32_t game_code = generateGameCode();
    // Game could receive game_code to inform the player when it asks for it.
    Game* game = new Game(MAX_PLAYERS);

    // Creates the smart pointer for RAII
    shared_ptr<CreateGameFeedback> create_feed =
            make_shared<CreateGameFeedback>(game_code);

    // Push feedback for the player before joining
    player_queue->push(create_feed);

    // Join the playe
    game->join(game_queue, player_queue, player_id);

    pair<uint32_t, Game*> hash(game_code, game);

    games.insert(hash);

    // The game will start sending feedback!
    game->start();
    cleanEmptyGames();

    return game_code;
}

bool GameManager::joinGame(Queue<std::shared_ptr<InGameCommand>> *&game_queue,
                           const std::shared_ptr<Queue<std::shared_ptr<Information>>> &player_queue,
                           std::uint8_t *player_id, std::uint32_t game_code) {
    using std::unique_lock;
    using std::mutex;

    unique_lock<mutex> lck(mtx);

    auto game = games.find(game_code);
    if (game == games.end())
        return false;

    if (game->second->isFull())
        return false;
    // Push success info

    game->second->join(game_queue, player_queue, player_id);
    return true;
}


GameManager::~GameManager() {
    cleanAllGames();
}
