#include "../../../include/GameLogic/Soldiers/scoutsoldier.h"

ScoutSoldier::ScoutSoldier(
    uint16_t x,
    uint16_t y,
    int8_t dir,
    uint8_t width,
    uint8_t height,
    uint8_t speed,
    uint16_t health,
    std::unique_ptr<Weapon>&& weapon,
    std::unique_ptr<Grenade>&& grenade) :
    Soldier(x, y, dir, width, height, speed, health, std::move(weapon), std::move(grenade)) {
}