// Copyright [2023] pgallino

#include "../include_handler.h"

Handler::Handler(Socket &&peer, Game &game) : 
    server_protocol(std::move(peer)),
    queue(MAX_SIZE),
    game(std::ref(game)),
    keep_talking(true),
    sender(std::ref(server_protocol), std::ref(queue), std::ref(keep_talking)),
    receiver(std::ref(server_protocol), std::ref(queue), std::ref(keep_talking)) {
}

void Handler::run(void) {
    receiver.start();
    sender.start();
}

bool Handler::are_dead(void) const {
    return ((sender.is_dead()) && (receiver.is_dead()));
}

void Handler::join(void) {
    receiver.join();
    sender.join();
}

void Handler::kill(void) {
    keep_talking = false;
    server_protocol.close_socket();
}
