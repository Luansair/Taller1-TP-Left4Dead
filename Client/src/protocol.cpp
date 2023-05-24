#include <netinet/in.h>
#include "../include/protocol.h"

Protocol::Protocol(Socket& socket) : socket(socket) {
}

void Protocol::sendAction(const Action &action) {
    std::vector<int8_t> action_vec = action.serialize();
    socket.sendData(action_vec.data(), action_vec.size());
}
