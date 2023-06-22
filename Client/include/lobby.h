//
// Created by luan on 16/06/23.
//

#ifndef TP_LOBBY_H
#define TP_LOBBY_H

#include <memory>
#include "../../Common/include/Information/information.h"
#include "../../libs/queue.h"

class ClientLobby {
    Queue<std::shared_ptr<Information>>& actions_to_send;
    Queue<std::shared_ptr<Information>>& feedback_received;
    bool soldier_picked;
    bool joined;

    void joinGame();
    void pickSoldier();
    uint8_t pickGameMode();
public:
    ClientLobby(Queue<std::shared_ptr<Information>>& actions_to_send,
                Queue<std::shared_ptr<Information>>& feedback_received);
    void launch();

    ClientLobby(const ClientLobby&) = delete;
    ClientLobby& operator=(const ClientLobby&) = delete;

    ~ClientLobby() = default;
};

#endif //TP_LOBBY_H
