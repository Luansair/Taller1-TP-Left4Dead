// Copyright [2023] pgallino

#include "../include/receiver.h"

Receiver::Receiver(Server_protocol& protocol, 
    Queue<std::vector<char>>& queue,
    const std::atomic<bool>& keep_talking) :
    protocol(std::ref(protocol)),
    queue(std::ref(queue)),
    is_running(true),
    keep_talking(keep_talking) {
}

void Receiver::run() { try {
    while (keep_talking) {
        bool was_closed = false;
        std::vector<char> message = protocol.receive_message(&was_closed);
        if (was_closed) break;
        queue.push(message);
    }
    is_running = false;
    } catch (ClosedSocket& err) {
        // revisar catcheos
        is_running = false;
    }
}

bool Receiver::is_dead(void) const {
    return !is_running;
}
