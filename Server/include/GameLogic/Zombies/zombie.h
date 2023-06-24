#ifndef ZOMBIE_H_
#define ZOMBIE_H_

#include "../position.h"
#include "../hitbox.h"
#include "../radialhitbox.h"
#include "../../../../Common/include/Information/information_code.h"

#include <utility>
#include <cstdint>
#include <map>
#include <memory>
#include <chrono>
#include <cmath>
#include <random>

class Throwable;
class Soldier;
class ThrowableFactory;

class Zombie {
public:
    uint32_t zombie_id;
    int8_t dir = LEFT;
    uint8_t axis = X;
    double speed;
    double health;
    double width;
    double height;
    Position position;
    std::shared_ptr<Soldier> att_vic;
    int8_t dir_x = LEFT;
    double sight = 200.0;
    double listening_range = 500.0;
    double hit_scope = 30.0;
    double damage_recv = 0.0;
    double damage = 0.2;
    uint32_t attacker_id = 500; // num cualquiera

    /* tiempos */
    std::chrono::_V2::system_clock::time_point last_step_time = std::chrono::system_clock::now();
    std::chrono::_V2::system_clock::time_point death_time = std::chrono::system_clock::now();
    std::chrono::_V2::system_clock::time_point being_hurt_time = std::chrono::system_clock::now();
    double die_cooldown = 10.0;

    /* estados */
    bool moving = false;
    bool attacking = false;
    bool dying = false;
    bool alive = true;
    bool being_hurt = false;
    bool screaming = false; // solo la witch debería.

    virtual ~Zombie() {}

    explicit Zombie(
    uint32_t zombie_id,
    double width,
    double height,
    double speed,
    double health);

    /* COMANDOS */

    virtual void move(
    uint8_t state,
    int8_t moveDirection);
    virtual void attack(uint8_t state, std::shared_ptr<Soldier> victim);
    virtual void idle(uint8_t state);
    virtual void recvDamage(uint8_t state, double damage, uint32_t attacker);
    virtual void die(uint8_t state);

    /* SIMULADORES */

    virtual void simulate(std::chrono::_V2::system_clock::time_point real_time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies, 
    std::map<uint32_t, std::shared_ptr<Throwable>>& throwables, double dim_x, double dim_y, ThrowableFactory& factory);
    virtual void simulateMove(std::chrono::_V2::system_clock::time_point real_time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies, 
    std::map<uint32_t, std::shared_ptr<Throwable>>& throwables, double dim_x, double dim_y, ThrowableFactory& factory);
    virtual void simulateAttack(void);
    virtual void simulateDie(std::chrono::_V2::system_clock::time_point real_time);
    virtual void simulateRecvDamage(std::chrono::_V2::system_clock::time_point real_time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers);
    virtual void detect_victim(bool *detected, uint32_t *victim, std::map<uint32_t,
    std::shared_ptr<Soldier>>& soldiers, double dim_x, double dim_y);
    virtual void detect_screaming_witch(bool *detected, uint32_t *witch_id, std::map<uint32_t, 
    std::shared_ptr<Zombie>>& zombies, double dim_x, double dim_y);
    virtual void CalculateNextPos_by_victim(double *next_x, double *next_y, 
    int8_t *direction, uint32_t victim_id, std::map<uint32_t, 
    std::shared_ptr<Soldier>>& soldiers, double time);
    virtual void CalculateNextPos_by_witch(double *next_x, double *next_y, 
    int8_t *direction, uint32_t witch_id, std::map<uint32_t, 
    std::shared_ptr<Zombie>>& zombies, double time);

    /* GETTERS */

    int8_t getDir(void);
    int8_t getDirX(void);
    double getHealth(void);
    double getWidth(void);
    double getHeight(void);
    uint32_t getId(void);
    virtual uint8_t getZombieType(void) = 0;
    virtual uint8_t getAction(void) = 0;
    Position& getPosition(void);
    const Position& seePosition(void) const;
    bool isDead(void);

    /* SETTERS */

    void setPosition(Position&& new_pos);
    void setRandomPosition(
            const std::map<uint32_t, std::shared_ptr<Soldier>> &soldiers,
            const std::map<uint32_t, std::shared_ptr<Zombie>> &zombies, double dim_x, double dim_y);

};

/* COMPARADORES PARA LA COLA DE PRIORIDAD DE SCOUT */

class Distance_from_left_is_minor {
public:
    bool operator()(std::shared_ptr<Zombie> below, std::shared_ptr<Zombie> above);
};

class Distance_from_right_is_minor {
public:
    bool operator()(std::shared_ptr<Zombie> below, std::shared_ptr<Zombie> above);
};

#endif  // ZOMBIE_H_
