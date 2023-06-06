#include "../include/game.h"

Game::Game(std::uint8_t max_players) :
        max_players(max_players),
        players_amount(0),
        is_running(true),
        started(false),
        commands_recv(10000),
        player_queues(),
        match(10, 10) { // por ahora se crea un match de 10x10
    player_queues.reserve(max_players);
}

/*
Game::addAdmin(std::uint8_t player_id) {
    if player id not in admins -> admins.push_back(player)
}
*/

bool Game::join(Queue<std::shared_ptr<InGameCommand>> *&game_queue, Queue<std::shared_ptr<Information>> &player_queue,
                std::uint8_t* player_id) {
    std::unique_lock<std::mutex> lck(mtx);
    if (started) {
        return false;
    }
    game_queue = &this->commands_recv;

    player_queues.push_back(&player_queue);

    // Also a random function could be used for the ids.
    *player_id = ++players_amount;

    // Game starts when max_players is reached.
    if (players_amount == max_players) {
        started = true;
    }
    return true;
}

bool Game::isEmpty() const {
    return players_amount == 0;
}

void Game::stop() {
    is_running = false;
}

void Game::run() {
    while (is_running && players_amount > 0) {
        // Use trypop, do not block the Game thread ever...
        // Command *command = nullptr;
        // if (commands_recv.try_pop(command)) command->Execute(std::ref(match));
        // delete command;
    }
}

Game::~Game() = default;
