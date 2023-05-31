#include "../include/protocol.h"
#include "../../Common/include/Action/action_code.h"
#include "../../Common/include/Action/action_startshoot.h"

Protocol::Protocol(Socket &socket) : socket(socket) {}

Action* Protocol::recvAction() {
    uint8_t action_id;
    socket.recvData(&action_id, 1);
    if (action_id == SHOOT) {
        uint8_t action_state;
        socket.recvData(&action_state, 1);
        if (action_state == ON) {
            return new StartShootAction();
        }
    }
    return nullptr;
}