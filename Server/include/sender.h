// Copyright [2023] pgallino

#ifndef TALLER1_TP_LEFT4DEAD_SENDER_H
#define TALLER1_TP_LEFT4DEAD_SENDER_H

#include <atomic>
#include <vector>
#include "../../libs/thread.h"
#include "../../libs/queue.h"
#include "protocol.h"

class Sender: public Thread {
private:
    Server_protocol& protocol;
    Queue<std::vector<char>>& queue;
    std::atomic<bool> is_running;
    const std::atomic<bool>& keep_talking;

protected:
    void run() override;

public:
    Sender(Server_protocol& protocol,
    Queue<std::vector<char>>& queue,
    const std::atomic<bool>& keep_talking);

    bool is_dead(void) const;

    Sender(const Sender&) = delete;
    Sender& operator=(const Sender&) = delete;

    Sender(Sender&&) = delete;
    Sender& operator=(Sender&&) = delete;
};

#endif //TALLER1_TP_LEFT4DEAD_SENDER_H
