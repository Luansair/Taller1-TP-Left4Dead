//
// Created by luan on 01/06/23.
//

#ifndef TP_STATE_CODE_H
#define TP_STATE_CODE_H

#include <cstdint>

enum ActionID : std::uint8_t {
    IDLE,
    SHOOT,
    MOVE,
    RELOAD,
    CHANGE_GRENADE,
    THROW,
    CREATE,
    JOIN,
};

enum Direction : std::uint8_t {
    RIGHT,
    LEFT
};

#endif //TP_STATE_CODE_H
