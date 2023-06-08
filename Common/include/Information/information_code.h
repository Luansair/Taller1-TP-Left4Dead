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

enum ElementType : std::uint8_t {
    SOLDIER_1,
    SOLDIER_2,
    SOLDIER_3,
    ZOMBIE,
    SPEAR,
    JUMPER,
    WITCH,
    VENOM
};

// Don't change or animations will break!
// Se puede agregar una señal para eliminar, id - update/erase - lo demas...
enum SoldierOneActionID : std::uint8_t {
    SOLDIER_1_ATTACK,
    SOLDIER_1_DEAD,
    SOLDIER_1_EXPLOSION,
    SOLDIER_1_GRENADE,
    SOLDIER_1_HURT,
    SOLDIER_1_IDLE,
    SOLDIER_1_RECHARGE,
    SOLDIER_1_RUN,
    SOLDIER_1_SHOOT_1,
    SOLDIER_1_SHOOT_2,
    SOLDIER_1_WALK,
};

enum SoldierOneGrenadeStatus : std::uint8_t {
    SOLDIER_1_GRENADE_IDLE,
    SOLDIER_1_GRENADE_EXPLOSION
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
