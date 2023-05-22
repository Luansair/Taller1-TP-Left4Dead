// Copyright [2023] pgallino

#ifndef TALLER1_TP_LEFT4DEAD_RECEIVER_H
#define TALLER1_TP_LEFT4DEAD_RECEIVER_H

#include <atomic>
#include <vector>
#include "../../libs/thread.h"
#include "../../libs/queue.h"
#include "protocol.h"

class Receiver: public Thread {
private:
    Server_protocol& protocol;
    Queue<std::vector<char>>& queue;
    std::atomic<bool> is_running;
    const std::atomic<bool>& keep_talking;

protected:
    void run() override;

public:
    Receiver(Server_protocol& protocol,
    Queue<std::vector<char>>& queue,
    const std::atomic<bool>& keep_talking);

    bool is_dead(void) const;

    Receiver(const Receiver&) = delete;
    Receiver& operator=(const Receiver&) = delete;

    Receiver(Receiver&&) = delete;
    Receiver& operator=(Receiver&&) = delete;
};

#endif //TALLER1_TP_LEFT4DEAD_RECEIVER_H
