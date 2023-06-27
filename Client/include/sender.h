//
// Created by luan on 09/06/23.
//

#ifndef TP_SENDER_H
#define TP_SENDER_H

#include <atomic>
#include <memory>
#include "../../Common/include/Information/information.h"
#include "../../libs/queue.h"
#include "../../libs/thread.h"
#include "protocol.h"

class Sender : public Thread {
    Queue<std::shared_ptr<Information>>& actions_to_send;
    Protocol protocol;
    std::atomic<bool> keep_sending;
    std::atomic<bool> is_running;

public:
    Sender(Queue<std::shared_ptr<Information>>& actions_to_send,
           GameSocket& socket);
    void run() override;
    void stop();
    [[nodiscard]] bool isDead() const;
    ~Sender() override = default;
};

#endif //TP_SENDER_H
