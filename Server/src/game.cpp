#include "../include/game.h"

Game::Game(std::uint8_t max_players) :
    max_players(max_players),
    players_amount(0),
    queue(10000),
    player_queues() {
    player_queues.reserve(max_players);
}

/*
Game::addAdmin(std::uint8_t player_id) {
    if player id not in admins -> admins.push_back(player)
}
*/

bool Game::join(Queue<Command>*& game_queue, Queue<GameState>*& player_queue,
          std::uint8_t* player_id) {
    if (players_amount >= max_players) {
        return false;
    }
    game_queue = &this->queue;
    player_queues.push_back(player_queue);

    // Also a random function could be used for the ids.
    *player_id = players_amount++;
    return true;
}

bool Game::isEmpty() const {
    return players_amount == 0;
}

void Game::run() {

}