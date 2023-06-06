#ifndef EVENT_ACTION_CODE_H_
#define EVENT_ACTION_CODE_H_

#include <cstdint>

enum InformationID : std::uint8_t {
    ACTION_IDLE,
    ACTION_SHOOT,
    ACTION_MOVE,
    REQUEST_CREATE_GAME,
    REQUEST_JOIN_GAME,
    FEEDBACK_CREATE_GAME,
    FEEDBACK_JOIN_GAME,
    FEEDBACK_GAME_STATE
};

enum ActionState : std::uint8_t {
    OFF,
    ON
};

enum MoveAxis : std::uint8_t {
    X,
    Y
};

enum MoveDirection : std::int8_t {
    NONE = 0,
    UP = 1,
    DOWN = -1,
    LEFT = -1,
    RIGHT = 1
};

enum DrawDirection : std::int8_t {
    DRAW_RIGHT,
    DRAW_LEFT
};

/*
 * Maybe it is better to have two movement actions: Walk and Run.
 * Light press send Walk and Normal press send Run.
 * It is not that important though.
 */
enum MoveForce : std::uint8_t {
    NORMAL = 1,
    STRONG = 2
};

#endif  // EVENT_ACTION_CODE_H_
