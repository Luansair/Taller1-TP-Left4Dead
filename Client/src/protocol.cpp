#include <netinet/in.h>
#include "../include/protocol.h"
#include "../../Common/include/Feedback/feedback_code.h"
#include "../../Common/include/Feedback/feedback_server_creategame.h"

Protocol::Protocol(GameSocket& socket) : socket(socket) {
}

void Protocol::sendAction(const Action &action) {
    std::vector<int8_t> action_vec = action.serialize();
    socket.sendData(action_vec.data(), action_vec.size());
}

ServerFeedback *Protocol::recvPreGameFeedback() {
    std::uint8_t feedback_type;
    socket.recvData(&feedback_type, 1);
    if (feedback_type == FeedbackType::FEED_CREATE) {
        std::uint32_t bigendian_game_code;
        socket.recvData(&bigendian_game_code, sizeof(bigendian_game_code));
        std::uint32_t game_code = ntohl(bigendian_game_code);
        return new CreateGameFeedback(game_code);
    }
    return nullptr;
}


