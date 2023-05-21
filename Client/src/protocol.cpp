#include <netinet/in.h>
#include "../include/protocol.h"

Protocol::Protocol(Socket& socket) : socket(socket) {
}

void Protocol::sendKeyPress(int event_type, int key_press) {
    using std::uint32_t;

    uint32_t event_type_big_end =
            htonl(static_cast<uint32_t>(event_type));
    uint32_t key_press_big_end =
            htonl(static_cast<uint32_t>(key_press));
    uint32_t input[2] = {event_type_big_end, key_press_big_end};
    socket.send(&input, sizeof(input));
}
