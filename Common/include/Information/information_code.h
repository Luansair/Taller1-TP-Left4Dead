#ifndef EVENT_ACTION_CODE_H_
#define EVENT_ACTION_CODE_H_

#include <cstdint>

enum InformationID : std::uint8_t {
    ACTION_IDLE,
    ACTION_SHOOT,
    ACTION_MOVE,
    ACTION_RELOAD,
    ACTION_THROW,
    ACTION_REVIVE,
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
// Se puede separar la info del server de la del user y despues con un
// case switch ir eligiendo asi no  debe recompilar todo con cada cambio.
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

enum SoldierTwoActionID : std::uint8_t {
    SOLDIER_2_ATTACK,
    SOLDIER_2_DEAD,
    SOLDIER_2_GRENADE,
    SOLDIER_2_HURT,
    SOLDIER_2_IDLE,
    SOLDIER_2_RECHARGE,
    SOLDIER_2_RUN,
    SOLDIER_2_SHOOT_1,
    SOLDIER_2_SHOOT_2,
    SOLDIER_2_WALK,
};

enum SoldierThreeActionID : std::uint8_t {
    SOLDIER_3_ATTACK,
    SOLDIER_3_DEAD,
    SOLDIER_3_GRENADE,
    SOLDIER_3_HURT,
    SOLDIER_3_IDLE,
    SOLDIER_3_RECHARGE,
    SOLDIER_3_RUN,
    SOLDIER_3_SHOOT_1,
    SOLDIER_3_SHOOT_2,
    SOLDIER_3_SMOKE,
    SOLDIER_3_WALK,
};

enum ZombieActionID : std::uint8_t {
    ZOMBIE_ATTACK_1,
    ZOMBIE_ATTACK_2,
    ZOMBIE_ATTACK_3,
    ZOMBIE_BITE,
    ZOMBIE_DEAD,
    ZOMBIE_HURT,
    ZOMBIE_IDLE,
    ZOMBIE_JUMP,
    ZOMBIE_RUN,
    ZOMBIE_WALK,
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

enum DrawDirection : std::uint8_t {
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
