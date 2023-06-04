//
// Created by luan on 24/05/23.
//

#ifndef TP_FEEDBACK_SERVER_H
#define TP_FEEDBACK_SERVER_H

#include <cstdint>
#include <vector>

// 0 1 <code> -> CREATE con exito
// 0 <code> -> CREATE con <code> = 0 es error con create
// 1 1/0 -> JOIN exito/sin exito
// 2 ... -> GAME STATE
class ServerFeedback {
protected:

    ServerFeedback() = default;

public:
    [[nodiscard]] virtual std::vector<std::int8_t> serialize() const = 0;

    ServerFeedback(ServerFeedback&&) = default;
    ServerFeedback& operator=(ServerFeedback&&) = delete;

    ServerFeedback(ServerFeedback&) = delete;
    ServerFeedback& operator=(ServerFeedback&) = delete;

    virtual ~ServerFeedback() = default;
};
#endif //TP_FEEDBACK_SERVER_H
