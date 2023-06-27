// Copyright [2023] pgallino

#ifndef ACCEPTER_H_
#define ACCEPTER_H_

#include <list>
#include <string>
#include <utility>
#include "../../libs/thread.h"
#include "../../Common/include/Socket/socket_game.h"
#include "game.h"
#include "receiver.h"
#include "game_manager.h"

class Accepter: public Thread {
private:
    GameSocket skt;
    GameManager game_manager;
    std::list<Receiver*> clients;

    void killAll();
    void reapDead();
protected:
    virtual void run() override;

public:
    explicit Accepter(const std::string& servname);

    void stop();

    virtual ~Accepter() override;
};

#endif  // ACCEPTER_H_
