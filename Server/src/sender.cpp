// Copyright [2023] pgallino

#include "../include/sender.h"

Sender::Sender(Server_protocol& protocol,
    Queue<std::vector<char>>& queue,
    const std::atomic<bool>& keep_talking) :
    protocol(std::ref(protocol)),
    queue(std::ref(queue)),
    is_running(true),
    keep_talking(keep_talking) {
}

void Sender::run() { try {
    while (keep_talking) {
        bool was_closed = false;
        std::vector<char> message = queue.pop();
        protocol.send_message(message, &was_closed);
        if (was_closed) break;
    }
    is_running = false;
    } catch (ClosedQueue& err) {
        // chequear catcheos
        is_running = false;
    }
}

bool Sender::is_dead(void) const {
    return !is_running;
}