#ifndef EVENT_ACTION_CODE_H_
#define EVENT_ACTION_CODE_H_

#include <cstdint>

enum class Action : std::uint8_t {
    IDLE,
    SHOOT,
    MOVE,
    RELOAD,
    CHANGE_GRENADE,
    THROW,
};

enum class ActionState : std::uint8_t {
    OFF,
    ON
};

enum class MoveAxis : std::uint8_t {
    X,
    Y
};

enum class MoveDirection : std::int8_t {
    NONE = 0,
    UP = 1,
    DOWN = -1,
    LEFT = -1,
    RIGHT = 1
};

/*
 * Maybe it is better to have two movement actions: Walk and Run.
 * Light press send Walk and Normal press send Run.
 * It is not that important though.
 */
enum class MoveForce : std::uint8_t {
    NORMAL = 1,
    STRONG = 2
};

#endif  // EVENT_ACTION_CODE_H_
