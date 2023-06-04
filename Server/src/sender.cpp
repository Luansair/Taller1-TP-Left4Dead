// Copyright [2023] pgallino

#include "../include/sender.h"

Sender::Sender(GameSocket& socket, Queue<ServerFeedback*>& game_state_queue) :
    protocol(socket),
    game_state_queue(game_state_queue),
    is_running(true) ,
    keep_talking(true) {
}

void Sender::run() {
    using std::cerr;
    using std::endl;
    try {
    while (keep_talking) {
        ServerFeedback* feed = game_state_queue.pop();
        protocol.sendFeedback(*feed);
    }
    is_running = false;
    } catch (const ClosedQueue& err) {
        cerr << "In Sender thread: " << err.what() << endl;
        is_running = false;
        keep_talking = false;
    } catch (const std::exception& e) {
        cerr << "An exception was caught in the Sender thread: "
        << e.what() << endl;
    } catch (...) {
        cerr << "An unknown exception was caught in the Sender thread." << endl;
    }

}

void Sender::stop() {
    keep_talking = false;
}

bool Sender::isDead() const {
    return !is_running;
}