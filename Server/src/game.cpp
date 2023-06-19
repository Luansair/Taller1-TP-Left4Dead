#include <chrono>
#include "../include/game.h"

Game::Game(std::uint8_t max_players) :
        max_players(max_players),
        players_amount(0),
        is_running(true),
        started(false),
        commands_recv(10000),
        player_queues(),
        match(1000.0, 1000.0) { // por ahora se crea un match de 10x10
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

    match.join(*player_id, actor++);
    if (actor == 3) actor = 0;

    if(!zombies) {
        setMatch(5); //seteo 5 zombies
    }

    // Game starts when max_players is reached.
    if (isFull()) {
        started = true;
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

    while (is_running && players_amount > 0) {

        sleep_for(milliseconds(5));
        std::unique_lock<std::mutex> lck(mtx);

        std::shared_ptr<InGameCommand> command (nullptr);

        if (commands_recv.try_pop(std::ref(command)))
            command->execute(std::ref(match));
        match.simulateStep();
        std::vector<std::pair<short unsigned int, ElementStateDTO>>state =
                match.getElementStates();

        const std::shared_ptr<Information>& feedback_ptr =
                std::make_shared<GameStateFeedback>(std::move(state));
        for (
                auto player_queue = player_queues.begin();
                player_queue !=player_queues.end(); ) {
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
    }
}

void Game::setMatch(int cant_zombies) {
    //le pongo 40 porque no hay todavia 40 soldados
    for(int i = 40; i < 40 + cant_zombies; i++) {
       match.setZombie(i,ZOMBIE); 
    }
    zombies = true;
}

bool Game::isFull() const {
    return players_amount >= max_players;
}

Game::~Game() = default;
