#ifndef SOLDIER_H_
#define SOLDIER_H_

#include "../Weapons/weapon.h"
#include "../Grenades/grenade.h"
#include "../Zombies/zombie.h"
#include "../position.h"
#include "../../../include/GameLogic/hitbox.h"
#include "../../../../Common/include/Information/information_code.h"

#include <map>
#include <memory>

class Soldier {

public:
    uint32_t soldier_id;
    int8_t dir;
    uint8_t axis = 0;
    int8_t speed;
    int16_t health;
    int8_t width;
    int8_t height;
    Position position;
    std::unique_ptr<Weapon> weapon;
    std::unique_ptr<Grenade> grenade;
    int8_t dir_x = RIGHT;
    bool moving = false;
    bool shooting = false;
    bool reloading = false;
    bool throwing = false;

    explicit Soldier(
    uint32_t soldier_id,
    int8_t dir,
    int8_t width,
    int8_t height,
    int8_t speed,
    int16_t health,
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
    virtual void idle(uint8_t state);
    virtual void recvDamage(int8_t damage);

    virtual void simulate(uint16_t time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies, int16_t dim_x, int16_t dim_y);

    virtual void simulateMove(uint16_t time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies, int16_t dim_x, int16_t dim_y);

    virtual void simulateShoot(uint16_t time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies);

    virtual void simulateReload(uint16_t time);
    virtual void simulateThrow(uint16_t time);

    int8_t getDir(void);
    int8_t getDirX(void);
    int8_t getHealth(void);
    uint8_t getWidth(void);
    uint8_t getHeight(void);
    uint32_t getId(void);
    virtual uint8_t getSoldierType(void) = 0;
    uint8_t getAction(void);

    void setPosition(Position&& new_pos);

    Position& getPosition(void);
    const Position& seePosition(void) const;

};

class Distance_from_left_is_minor {
public:
    bool operator()(std::shared_ptr<Soldier> below, std::shared_ptr<Soldier> above);
};

class Distance_from_right_is_minor {
public:
    bool operator()(std::shared_ptr<Soldier> below, std::shared_ptr<Soldier> above);
};

#endif  // SOLDIER_H_
