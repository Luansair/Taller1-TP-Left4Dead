#include "../../../include/GameLogic/Soldiers/idfsoldier.h"

IdfSoldier::IdfSoldier(
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

uint8_t IdfSoldier::getSoldierType(void) {
    return SOLDIER_1;
}

uint8_t IdfSoldier::getAction(void) {
    if (shooting) return SOLDIER_1_SHOOT_1;
    if (moving) return SOLDIER_1_RUN;
    if (reloading) return SOLDIER_1_RECHARGE;
    if (throwing) return SOLDIER_1_GRENADE_EXPLOSION;
    return SOLDIER_1_IDLE;
}
