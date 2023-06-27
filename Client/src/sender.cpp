//
// Created by luan on 12/06/23.
//
#include "../include/sender.h"

Sender::Sender(Queue<std::shared_ptr<Information>> &actions_to_send,
               GameSocket& socket) :
    actions_to_send(actions_to_send),
    protocol(socket),
    keep_sending(true),
    is_running(true) {
}

void Sender::run() {
    using std::cerr;
    using std::endl;
    try {
        while (keep_sending) {
            const std::shared_ptr<Information>& action_to_send =
                    actions_to_send.pop();
            protocol.sendAction(*action_to_send);
        }
    } catch (const ClosedQueue& err) {
        cerr << "In Sender thread: " << err.what() << endl;
        keep_sending = false;
    } catch (const std::exception& e) {
        cerr << "An exception was caught in the Sender thread: "
             << e.what() << endl;
        keep_sending = false;
    } catch (...) {
        cerr << "An unknown exception was caught in the Sender thread." << endl;
        keep_sending = false;
    }
    is_running = false;
}

void Sender::stop() {
    keep_sending = false;
    actions_to_send.close();
}

bool Sender::isDead() const {
    return !is_running;
}