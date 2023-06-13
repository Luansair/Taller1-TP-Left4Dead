//
// Created by luan on 09/06/23.
//

#ifndef TP_RECEIVER_H
#define TP_RECEIVER_H

#include <atomic>
#include <memory>
#include "../../Common/include/Information/information.h"
#include "../../libs/queue.h"
#include "../../libs/thread.h"
#include "protocol.h"

class Receiver : public Thread {
    Queue<std::shared_ptr<Information>>& feedback_received;
    Protocol protocol;
    std::atomic<bool> is_running;
    std::atomic<bool> keep_receiving;

public:
    Receiver(Queue<std::shared_ptr<Information>>& feedback_received,
             GameSocket& socket);
    void stop();
    void run() override;
    [[nodiscard]] bool isDead() const;
    ~Receiver() override = default;
};

#endif //TP_RECEIVER_H
