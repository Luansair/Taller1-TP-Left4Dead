#include "../include/client.h"

Client::Client(const char *hostname, const char *servname) :
    socket(hostname, servname) ,
    actions_to_send(5000),
    feedback_received(10000),
    sender(actions_to_send, socket),
    receiver(feedback_received, socket),
    lobby(actions_to_send, feedback_received),
    client_game(actions_to_send, feedback_received) {

}

void Client::start() {

    sender.start();
    receiver.start();

    lobby.launch();
    client_game.launch();
}

Client::~Client() {

    if (!receiver.isDead()) {
        receiver.stop();
    }
    if(!sender.isDead()) {
        sender.stop();
    }
    receiver.join();
    sender.join();
}
