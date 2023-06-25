//
// Created by luan on 16/06/23.
//

#ifndef TP_LOBBY_H
#define TP_LOBBY_H

#include <memory>
#include <QApplication>
#include "../../Common/include/Information/information.h"
#include "../../libs/queue.h"


class ClientLobby {
    int argc;
    char **argv;
    Queue<std::shared_ptr<Information>>& actions_to_send;
    Queue<std::shared_ptr<Information>>& feedback_received;
    bool soldier_picked;
    bool joined;

    void joinGame();
    void pickSoldier();
    uint8_t pickGameMode();
    uint8_t pickGameDifficulty();
public:
    ClientLobby(Queue<std::shared_ptr<Information>> &actions_to_send,
                Queue<std::shared_ptr<Information>> &feedback_received, int argc, char **argv);
    void launch();

    ClientLobby(const ClientLobby&) = delete;
    ClientLobby& operator=(const ClientLobby&) = delete;

    ~ClientLobby() = default;
};

#endif //TP_LOBBY_H
