#ifndef SCOUTSOLDIER_H_
#define SCOUTSOLDIER_H_

#include "soldier.h"

class ScoutSoldier : public Soldier {
private:
    int32_t x;
    int32_t y;
    int8_t dir;
    int8_t health;
    std::unique_ptr<Weapon> weapon;
    std::unique_ptr<Grenade> grenade;

public:
    explicit ScoutSoldier(int8_t health, std::unique_ptr<Weapon> &&weapon, std::unique_ptr<Grenade> &&grenade);

    void move(GameMap &map,
    uint8_t state,
    uint8_t moveAxis,
    int8_t moveDirection,
    uint8_t moveForce) override;

    void shoot(GameMap &map, uint8_t state) override;

    void reload(uint8_t state) override;

    void throwGrenade(GameMap &map) override;

    void cGrenade(void) override;

    void recvDamage(int8_t damage) override;

    void setPos(int32_t x, int32_t y, int8_t dir) override;

    int32_t getXPos(void) override;
    int32_t getYPos(void) override;
    int8_t getDir(void) override;
    int8_t getHealth(void) override;
};

#endif  // SCOUTSOLDIER_H_
