#include "../../../include/GameLogic/Soldiers/p90soldier.h"

P90Soldier::P90Soldier(
    uint32_t soldier_id,
    int8_t dir,
    int8_t width,
    int8_t height,
    int8_t speed,
    int16_t health,
    std::unique_ptr<Weapon>&& weapon,
    std::unique_ptr<Grenade>&& grenade) :
    Soldier(soldier_id, dir, width, height, speed, health, std::move(weapon), std::move(grenade)) {
}

uint8_t P90Soldier::getSoldierType(void) {
    return SOLDIER_2;
}

// cambiar a soldier_2
uint8_t P90Soldier::getAction(void) {
    if (shooting) return SOLDIER_1_SHOOT_1;
    if (moving) return SOLDIER_1_RUN;
    if (reloading) return SOLDIER_1_RECHARGE;
    if (throwing) return SOLDIER_1_GRENADE_EXPLOSION;
    return SOLDIER_1_IDLE;
}
