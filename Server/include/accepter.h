// Copyright [2023] pgallino

#ifndef ACCEPTER_H_
#define ACCEPTER_H_

#include <list>
#include <string>
#include <utility>
#include "../../libs/thread.h"
#include "../../Common/include/socket.h"
#include "game.h"
#include "receiver.h"
#include "game_manager.h"

class Accepter: public Thread {
private:
    Socket skt;
    GameManager game_manager;
    std::list<Receiver*> clients;

    void killAll();
    void reapDead();
protected:
    virtual void run() override;

public:
    explicit Accepter(const std::string& servname);

    void stop();

    Accepter(const Accepter&) = delete;
    Accepter& operator=(const Accepter&) = delete;

    Accepter(Accepter&&) = delete;
    Accepter& operator=(Accepter&&) = delete;

    virtual ~Accepter() override;
};

#endif  // ACCEPTER_H_
