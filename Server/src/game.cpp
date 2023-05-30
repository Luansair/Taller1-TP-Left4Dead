#include "../include/game.h"

Game::Game(std::uint8_t max_players) :
        max_players(max_players),
        players_amount(0),
        is_running(true),
        commands_recv(10000),
        player_queues(),
        match(100, 100) { // por ahora se crea un match de 100x100
    player_queues.reserve(max_players);
}

/*
Game::addAdmin(std::uint8_t player_id) {
    if player id not in admins -> admins.push_back(player)
}
*/

bool Game::join(Queue<Command *> *&game_queue, Queue<GameState *> &player_queue,
                std::uint8_t* player_id) {

    // If a player leaves and at the same time Game manager access to its value
    // it could lead to a Race Cond. Need locks or be atomic
    if (players_amount >= max_players) {
        return false;
    }
    game_queue = &this->commands_recv;

    // Mandatory lock. Game uses this to send information. Game Manager (from
    // Receiver thread) uses this to add new players. Likely RC...
    player_queues.push_back(&player_queue);

    // Also a random function could be used for the ids.
    *player_id = ++players_amount;
    return true;
}

bool Game::isEmpty() const {
    // Need locks or be atomic.
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

Game::~Game() {
    Command* cmd = nullptr;
    while (commands_recv.try_pop(cmd)) {
        delete cmd;
        cmd = nullptr;
    }
}
