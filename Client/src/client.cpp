#include "../include/client.h"

Client::Client(int argc, char **argv) :
    socket(argv[1], argv[2]) ,
    actions_to_send(5000),
    feedback_received(10000),
    sender(actions_to_send, socket),
    receiver(feedback_received, socket),
    lobby(actions_to_send, feedback_received, argc, argv),
    client_game(actions_to_send, feedback_received) {

}

void Client::start() {

    sender.start();
    receiver.start();

    lobby.launch();
    client_game.launch(lobby);
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
