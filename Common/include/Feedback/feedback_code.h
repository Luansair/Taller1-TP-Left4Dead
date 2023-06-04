//
// Created by luan on 04/06/23.
//

#ifndef TP_FEEDBACK_CODE_H
#define TP_FEEDBACK_CODE_H

#include <cstdint>

enum FeedbackType : std::uint8_t {
    FEED_CREATE,
    FEED_JOIN,
    FEED_GAME,
};

#endif //TP_FEEDBACK_CODE_H
