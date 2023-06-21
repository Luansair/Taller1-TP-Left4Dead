#ifndef CLIENT_H_
#define CLIENT_H_

#include "../../Common/include/Socket/socket_game.h"
#include "protocol.h"
#include "../../libs/queue.h"
#include "visual_game.h"
#include "sender.h"
#include "receiver.h"
#include "game.h"
#include "lobby.h"

class Client {
    GameSocket socket;
    Queue<std::shared_ptr<Information>> actions_to_send;
    Queue<std::shared_ptr<Information>> feedback_received;
    Sender sender;
    Receiver receiver;
    ClientLobby lobby;
    ClientGame client_game;

public:
    Client(const char* hostname, const char* servname);

    void start();

    Client(Client&&) = delete;
    Client& operator=(Client&&) = delete;

    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;

    ~Client();
};

#endif  // CLIENT_H_
