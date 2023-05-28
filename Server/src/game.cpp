#include "../include/game.h"

Game::Game(std::uint8_t max_players) :
        max_players(max_players),
        players_amount(0),
        is_running(true),
        commands_recv(10000),
        player_queues() {
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
    }
}

/*
LOGICA DE JUEGO; PODRIA MODULARIZARSE EN OTRA CLASE
*/

void Game::shoot(uint8_t player_id, uint8_t state) {
    // encuentro jugador en un map de clase jugador
    // disparo o dejo de disparar con state
    // ejecuto colisiones
}

void Game::move(uint8_t player_id,
        uint8_t state,
        uint8_t moveAxis,
        int8_t moveDirection,
        uint8_t moveForce) {
            // encuentro jugador en un map de clase jugador
            // le cambio la posicion
        }

void Game::reload(uint8_t player_id, uint8_t state) {
    // encuentro jugador en un map de clase jugador
    // recargo o dejo de recargar con state
}

void Game::cgrenade(uint8_t player_id) {
    // encuentro jugador en un map de clase jugador
    // cambio granada
}

void Game::throwgrenade(uint8_t player_id) {
    // encuentro jugador en un map de clase jugador
    // tiro granada
    // ejecuto colisiones
}

Game::~Game() {
    Command* cmd = nullptr;
    while (commands_recv.try_pop(cmd)) {
        delete cmd;
        cmd = nullptr;
    }
}