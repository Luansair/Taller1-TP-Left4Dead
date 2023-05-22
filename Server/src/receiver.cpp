// Copyright [2023] pgallino

#include "../include/receiver.h"

#define SHUT_RDWR 2

Receiver::Receiver(Socket &&peer, GameManager& game_manager) :
    peer(std::move(peer)),
    protocol(peer),
    game_state_queue(5000) ,
    sender(peer, game_state_queue),
    game_manager(game_manager),
    is_running(true),
    keep_talking(true),
    joined(false) { }

void Receiver::run() { try {
    while (keep_talking && !joined) {
        int8_t dummy;
        peer.recv(&dummy, 1);

        joined = true;
        sender.start();
    }
    is_running = false;
    } catch (ClosedSocket& err) {
        // revisar catcheos
        is_running = false;
        keep_talking = false;
    }
}

void Receiver::stop() {
    keep_talking = false;
    peer.shutdown(SHUT_RDWR);
    peer.close();
    game_state_queue.close();
}

bool Receiver::isDead() const {
    return !is_running;
}

Receiver::~Receiver() {
    if (joined) {
        if (!sender.isDead()) {
            sender.stop();
        }
        sender.join();
    }
}
