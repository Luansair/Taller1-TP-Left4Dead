#include <chrono>
#include "../include/game.h"

Game::Game(std::uint8_t max_players, uint8_t gameMode, uint8_t gameDifficulty, uint32_t game_code) :
        max_players(max_players),
        players_amount(0),
        is_running(true),
        started(false),
        commands_recv(10000),
        player_queues(),
        match(nullptr) {
    selectMode(gameMode, gameDifficulty, game_code);
    player_queues.reserve(max_players);
}

/*
Game::addAdmin(std::uint8_t player_id) {
    if player id not in admins -> admins.push_back(player)
}
*/

void Game::join(Queue<std::shared_ptr<InGameCommand>> *&game_queue, const std::shared_ptr<Queue<std::shared_ptr<Information>>> &player_queue,
                std::uint8_t* player_id) {
    std::unique_lock<std::mutex> lck(mtx);

    game_queue = &this->commands_recv;

    player_queues.push_back(player_queue);

    // Also a random function could be used for the ids.
    *player_id = ++players_amount;

    // Game starts when max_players is reached.
    if (isFull()) {
        started = true;
    }
}

void Game::selectMode(uint8_t gameMode, uint8_t gameDifficulty, uint32_t game_code) {
    switch (gameMode)
    {
    case SURVIVAL:

        match = std::shared_ptr<Match>(new Survival(50000, 200.0, gameDifficulty, game_code));
        break;
    
    case CLEAR_THE_ZONE:
        match = std::shared_ptr<Match>(new ClearTheZone(50000, 200.0, gameDifficulty, game_code));
        break;
    }
}

bool Game::isEmpty() const {
    return players_amount == 0;
}

void Game::stop() {
    is_running = false;
}

void Game::run() {
    using std::this_thread::sleep_for;
    using std::chrono::milliseconds;
    using std::chrono::_V2::system_clock;

    while (is_running && players_amount > 0) {
        std::chrono::_V2::system_clock::time_point start = std::chrono::system_clock::now();
        sleep_for(milliseconds(5));
        std::unique_lock<std::mutex> lck(mtx);

        std::shared_ptr<InGameCommand> command (nullptr);

        if (commands_recv.try_pop(std::ref(command)))
            command->execute(match);
        if (!(match->is_over())) {
            match->simulateStep(start);
            std::vector<std::pair<short unsigned int, ElementStateDTO>>state = match->getElementStates();
            const std::shared_ptr<Information>& feedback_ptr = std::make_shared<GameStateFeedback>(std::move(state));
            for (auto player_queue = player_queues.begin(); player_queue !=player_queues.end(); ) {
                try {
                    if (!(*player_queue)) {
                        player_queue = player_queues.erase(player_queue);
                        continue;
                    }
                    if (!(*player_queue)->try_push(feedback_ptr)) {
                        player_queue = player_queues.erase(player_queue);
                        continue;
                    }
                } catch(const ClosedQueue& e) {
                    std::cout << e.what() << std::endl;
                    player_queues.erase(player_queue);
                    continue;
                }
                player_queue++;
            }
            continue;
        }
        // si se terminó, mando el score
        std::vector<std::pair<short unsigned int, ScoreDTO>>score = match->getScores();
        const std::shared_ptr<Information>& feedback_ptr = std::make_shared<GameScoreFeedback>(std::move(score));
        for (auto player_queue = player_queues.begin(); player_queue !=player_queues.end(); ) {
            try {
                if (!(*player_queue)) {
                    player_queue = player_queues.erase(player_queue);
                    continue;
                }
                if (!(*player_queue)->try_push(feedback_ptr)) {
                    player_queue = player_queues.erase(player_queue);
                    continue;
                }
            } catch(const ClosedQueue& e) {
                std::cout << e.what() << std::endl;
                player_queues.erase(player_queue);
                continue;
            }
            player_queue++;
        }
        is_running = false;
    }
}

bool Game::isFull() const {
    return players_amount >= max_players;
}

Game::~Game() = default;
