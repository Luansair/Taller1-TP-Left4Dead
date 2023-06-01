// Copyright [2023] pgallino

#ifndef SENDER_H_
#define SENDER_H_

#include <atomic>
#include <vector>
#include "../../libs/thread.h"
#include "../../libs/queue.h"
#include "protocol.h"
#include "game_state.h"

class Sender: public Thread {
private:
    Protocol protocol;
    Queue<GameState*>& game_state_queue;

    std::atomic<bool> is_running;
    std::atomic<bool> keep_talking;

protected:
    void run() override;

public:
    Sender(GameSocket& peer, Queue<GameState*>& game_state_queue);

    bool isDead() const;

    void stop();

    Sender(const Sender&) = delete;
    Sender& operator=(const Sender&) = delete;

    Sender(Sender&&) = delete;
    Sender& operator=(Sender&&) = delete;
};

#endif // SENDER_H_
