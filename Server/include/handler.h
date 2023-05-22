// Copyright [2023] pgallino

#ifndef TALLER1_TP_LEFT4DEAD_HANDLER_H
#define TALLER1_TP_LEFT4DEAD_HANDLER_H

#include <utility>
#include <string>
#include <cstdint>
#include <iostream>
#include <vector>
#include <map>
#include <mutex>
#include <atomic>
#include "protocol.h"
#include "../../libs/thread.h"
#include "game.h"
#include "sender.h"
#include "receiver.h"
#define MAX_SIZE 10

class Handler {
    private:
    Server_protocol server_protocol;
    Queue<std::vector<char>> queue;
    Game& game;
    std::atomic<bool> keep_talking;
    Sender sender;
    Receiver receiver;

    public:
    Handler(Socket &&peer, Game &game);

    void lanzar_hilos(void);

    bool are_dead(void) const;

    void kill(void);
    void join(void);

    Handler(const Handler&) = delete;
    Handler& operator=(const Handler&) = delete;

    Handler(Handler&&) = delete;
    Handler& operator=(Handler&&) = delete;
};


#endif //TALLER1_TP_LEFT4DEAD_HANDLER_H
