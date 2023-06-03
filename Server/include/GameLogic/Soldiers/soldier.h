#ifndef SOLDIER_H_
#define SOLDIER_H_

#include "../Weapons/weapon.h"
#include "../Grenades/grenade.h"
#include "../../../../Common/include/Action/action_code.h"

#include <memory>

class Soldier {

public:
    uint16_t x;
    uint16_t y;
    int8_t dir;
    uint8_t width;
    uint8_t height;
    uint8_t speed;
    uint16_t health;
    std::unique_ptr<Weapon> weapon;
    std::unique_ptr<Grenade> grenade;

    explicit Soldier(
    uint16_t x, 
    uint16_t y,
    int8_t dir,
    uint8_t width,
    uint8_t height,
    uint8_t speed,
    uint16_t health,
    std::unique_ptr<Weapon>&& weapon,
    std::unique_ptr<Grenade>&& grenade);

    virtual ~Soldier() {}

    virtual void move(
    uint8_t state,
    uint8_t moveAxis,
    int8_t moveDirection,
    uint8_t moveForce);

    virtual void shoot(uint8_t state);

    virtual void reload(uint8_t state);

    virtual void throwGrenade(void);

    virtual void cGrenade(void);

    virtual void recvDamage(int8_t damage);

    virtual void setPos(uint16_t x, uint16_t y, int8_t dir);

    uint16_t getXPos(void);
    uint16_t getYPos(void);
    int8_t getDir(void);
    int8_t getHealth(void);

};

#endif  // SOLDIER_H_
