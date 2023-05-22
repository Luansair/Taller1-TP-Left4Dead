// Copyright [2023] pgallino

#include "../include/sender.h"

Sender::Sender(Socket& socket, Queue<int>& game_state_queue) :
    protocol(socket),
    game_state_queue(game_state_queue) ,
    is_running(true) ,
    keep_talking(true) {
}

void Sender::run() { try {
    while (keep_talking) {
        int dummy = game_state_queue.pop();
        if (dummy < 0)
            keep_talking = false;
    }
    is_running = false;
    } catch (ClosedQueue& err) {
        // chequear catcheos
        is_running = false;
        keep_talking = false;
    }
}

void Sender::stop() {
    keep_talking = false;
}

bool Sender::isDead() const {
    return !is_running;
}