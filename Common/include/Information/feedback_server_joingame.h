//
// Created by luan on 16/06/23.
//

#ifndef TP_FEEDBACK_SERVER_JOINGAME_H
#define TP_FEEDBACK_SERVER_JOINGAME_H

#include "information.h"

class JoinGameFeedback : public Information {
public:
    const std::uint8_t joined;

    explicit JoinGameFeedback(std::uint8_t joined);

    [[nodiscard]] std::vector<std::int8_t> serialize() const override;

    [[nodiscard]] std::uint8_t get_type(void) const override;

    JoinGameFeedback(const JoinGameFeedback&) = delete;
    JoinGameFeedback& operator=(const JoinGameFeedback&) = delete;

    ~JoinGameFeedback() override = default;
};

#endif //TP_FEEDBACK_SERVER_JOINGAME_H
