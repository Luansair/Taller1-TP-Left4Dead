#ifndef SOLDIER_H_
#define SOLDIER_H_

#include "../Weapons/weapon.h"
#include "../Grenades/grenade.h"
#include "../Zombies/zombie.h"
#include "../../../../Common/include/Action/action_code.h"

#include <map>
#include <memory>

class Soldier {

public:
    uint16_t x;
    uint16_t y;
    int8_t dir;
    uint8_t axis = 0;
    uint16_t next_x = 0;
    uint16_t next_y = 0;
    uint8_t width;
    uint8_t height;
    uint8_t speed;
    uint16_t health;
    std::unique_ptr<Weapon> weapon;
    std::unique_ptr<Grenade> grenade;
    bool moving = false;
    bool shooting = false;
    bool reloading = false;
    bool throwing = false;

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
    virtual void throwGrenade(uint8_t state);
    virtual void cGrenade(void);
    virtual void recvDamage(int8_t damage);

    virtual void simulateStep(uint16_t time);

    virtual void simulateMove(uint16_t time,
    std::map<uint32_t, std::unique_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::unique_ptr<Zombie>>& zombies);

    virtual void simulateShoot(uint16_t time,
    std::map<uint32_t, std::unique_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::unique_ptr<Zombie>>& zombies);

    virtual void simulateReload(uint16_t time);
    virtual void simulateThrow(uint16_t time);

    void collides(uint16_t x_other, uint16_t y_other, uint8_t width_other, uint8_t height_other);

    virtual void setPos(uint16_t x, uint16_t y, int8_t dir);
    uint16_t getXPos(void);
    uint16_t getYPos(void);
    uint8_t getWidth(void);
    uint8_t getHeight(void);
    int8_t getDir(void);
    int8_t getHealth(void);

};

#endif  // SOLDIER_H_
