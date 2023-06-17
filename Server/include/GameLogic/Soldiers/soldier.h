#ifndef SOLDIER_H_
#define SOLDIER_H_

#include "../Weapons/weapon.h"
#include "../Grenades/grenade.h"
#include "../Zombies/zombie.h"
#include "../position.h"
#include "../hitbox.h"
#include "../../../../Common/include/Information/information_code.h"

#include <map>
#include <memory>

class Soldier {

public:
    uint32_t soldier_id;
    int8_t dir = RIGHT;
    uint8_t axis = X;
    double speed;
    double health;
    double width;
    double height;
    Position position;
    std::unique_ptr<Weapon> weapon;
    std::unique_ptr<Grenade> grenade;
    int8_t dir_x = RIGHT;
    bool moving = false;
    bool shooting = false;
    bool reloading = false;
    bool throwing = false;
    bool alive = true;

    explicit Soldier(
    uint32_t soldier_id,
    double width,
    double height,
    double speed,
    double health,
    std::unique_ptr<Weapon>&& weapon,
    std::unique_ptr<Grenade>&& grenade);

    virtual ~Soldier() = default;

    Soldier(Soldier&&) = default;
    Soldier& operator=(Soldier&&) = default;

    Soldier(const Soldier&) = delete;
    Soldier& operator=(const Soldier&) = delete;

    /* COMANDOS */

    virtual void move(
    uint8_t state,
    uint8_t moveAxis,
    int8_t moveDirection,
    uint8_t moveForce);
    virtual void shoot(uint8_t state);
    virtual void reload(uint8_t state);
    virtual void throwGrenade(uint8_t state);
    virtual void idle(uint8_t state);
    virtual void recvDamage(double damage);

    /* SIMULADORES */

    virtual void simulate(double time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies, double dim_x, double dim_y);
    virtual void simulateMove(double time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies, double dim_x, double dim_y);
    virtual void simulateShoot(double time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies,
    double dim_x);
    virtual void simulateReload(double time);
    virtual void simulateThrow(double time);

    /* GETTERS */

    int8_t getDir();
    int8_t getDirX();
    double getHealth();
    double getWidth();
    double getHeight();
    uint32_t getId();
    virtual uint8_t getSoldierType() = 0;
    virtual uint8_t getAction() = 0;
    Position& getPosition();
    [[nodiscard]] const Position& seePosition() const;

    /* SETTERS */

    void setPosition(Position&& new_pos);
    void setRandomPosition(
            const std::map<uint32_t, std::shared_ptr<Soldier>> &soldiers,
            const std::map<uint32_t, std::shared_ptr<Zombie>> &zombies, double dim_x, double dim_y);
};

/* COMPARADORES PARA LA COLA DE PRIORIDAD DE SCOUT */

class Distance_from_left_is_minor {
public:
    bool operator()(std::shared_ptr<Soldier> below, std::shared_ptr<Soldier> above);
};

class Distance_from_right_is_minor {
public:
    bool operator()(std::shared_ptr<Soldier> below, std::shared_ptr<Soldier> above);
};

#endif  // SOLDIER_H_
