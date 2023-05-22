// Copyright [2023] pgallino

#ifndef TALLER1_TP_LEFT4DEAD_ACCEPTER_H
#define TALLER1_TP_LEFT4DEAD_ACCEPTER_H

#include <list>
#include <string>
#include <utility>
#include "../../libs/thread.h"
#include "../../common/include/socket.h"
#include "game.h"
#include "handler.h"

class Accepter: public Thread {
private:
    Socket skt;
    Game game;
    std::list<Handler*> handlers;

protected:
    void run(void) override;

public:
    explicit Accepter(const std::string& servname);

    void close(void);

    void kill_all(void);

    void reap_dead(void);

    Accepter(const Accepter&) = delete;
    Accepter& operator=(const Accepter&) = delete;

    Accepter(Accepter&&) = delete;
    Accepter& operator=(Accepter&&) = delete;
};

#endif //TALLER1_TP_LEFT4DEAD_ACCEPTER_H
