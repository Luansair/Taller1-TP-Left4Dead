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
    REQUEST_PICK_IDF_SOLDIER,
    REQUEST_PICK_P90_SOLDIER,
    REQUEST_PICK_SCOUT_SOLDIER,
    REQUEST_SURVIVAL,
    REQUEST_CLEAR_THE_ZONE,
    REQUEST_EASY,
    REQUEST_NORMAL,
    REQUEST_HARD,
    REQUEST_INSANE,
    FEEDBACK_CREATE_GAME,
    FEEDBACK_JOIN_GAME,
    FEEDBACK_GAME_STATE
};

enum GameMode : std::uint8_t {
    CLEAR_THE_ZONE,
    SURVIVAL
};

enum GameDifficulty : std::uint8_t {
    DEASY,
    DNORMAL,
    DHARD,
    DINSANE
};

enum ActorType : std::uint8_t {
    SOLDIER_IDF,
    SOLDIER_P90,
    SOLDIER_SCOUT,
    ZOMBIE,
    SPEAR,
    JUMPER,
    WITCH,
    VENOM
};

enum BackgroundType : std::uint8_t {
    BACKGROUND_WAR1,
    BACKGROUND_WAR2,
    BACKGROUND_WAR3,
    BACKGROUND_WAR4,
    BACKGROUND_TYPE_LAST
};

#define WAR_1_BEHIND_COUNT 7
#define WAR_1_FRONT_COUNT 1
// Don't change the order. 
enum War1LayerType : std::uint8_t {
    WAR_1_LAYER_FENCE,
    WAR_1_LAYER_HOUSE_1,
    WAR_1_LAYER_HOUSE_2,
    WAR_1_LAYER_HOUSE_3,
    WAR_1_LAYER_ROAD,
    WAR_1_LAYER_RUINS,
    WAR_1_LAYER_SKY,
    WAR_1_LAYER_SUN,
    WAR_1_LAYER_LAST
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

enum WitchActionID : std::uint8_t {
    WITCH_ATTACK_1,
    WITCH_ATTACK_2,
    WITCH_ATTACK_3,
    WITCH_DEAD,
    WITCH_HURT,
    WITCH_IDLE,
    WITCH_JUMP,
    WITCH_RUN,
    WITCH_SCREAM,
    WITCH_WALK,
};

enum JumperActionID : std::uint8_t {
    JUMPER_ATTACK_1,
    JUMPER_ATTACK_2,
    JUMPER_ATTACK_3,
    JUMPER_DEAD,
    JUMPER_EATING,
    JUMPER_HURT,
    JUMPER_IDLE,
    JUMPER_JUMP,
    JUMPER_RUN,
    JUMPER_WALK,
};

enum VenomActionID : std::uint8_t {
    VENOM_ATTACK_1,
    VENOM_ATTACK_1A,
    VENOM_ATTACK_2,
    VENOM_DEAD,
    VENOM_HURT,
    VENOM_IDLE,
    VENOM_JUMP,
    VENOM_RUN,
    VENOM_WALK,
};

enum SpearActionID : std::uint8_t {
    SPEAR_ATTACK_1,
    SPEAR_ATTACK_2,
    SPEAR_DEAD,
    SPEAR_FALL,
    SPEAR_HURT,
    SPEAR_IDLE,
    SPEAR_PROTECT,
    SPEAR_RUN,
    SPEAR_RUN_ATTACK,
    SPEAR_WALK,
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
