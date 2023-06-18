#include "../../../include/GameLogic/Soldiers/p90soldier.h"

P90Soldier::P90Soldier(
    uint32_t soldier_id,
    double width,
    double height,
    double speed,
    double health,
    std::unique_ptr<Weapon>&& weapon,
    std::unique_ptr<Grenade>&& grenade) :
    Soldier(soldier_id, width, height, speed, health, std::move(weapon), std::move(grenade)) {
}

uint8_t P90Soldier::getSoldierType(void) {
    return SOLDIER_2;
}

// cambiar a soldier_2
uint8_t P90Soldier::getAction(void) {
    if (!alive) return SOLDIER_1_DEAD;
    if (shooting) return SOLDIER_1_SHOOT_1;
    if (moving) return SOLDIER_1_RUN;
    if (reloading) return SOLDIER_1_RECHARGE;
    if (throwing) return SOLDIER_1_GRENADE_EXPLOSION;
    return SOLDIER_1_IDLE;
}
