#ifndef CLIENT_H_
#define CLIENT_H_

#include "../../Common/include/Socket/socket_game.h"
#include "protocol.h"
#include "../../libs/queue.h"
#include "visual_game.h"
#include "sender.h"
#include "receiver.h"

class Client {
    GameSocket socket;
    Protocol protocol;
    Queue<std::shared_ptr<Information>> actions_to_send;
    Queue<std::shared_ptr<Information>> feedback_received;
    Sender sender;
    Receiver receiver;

    void processEvent(std::uint32_t event_type, int key_code, bool* quit);
    void lobbyProcess();
    void gameProcess();
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
