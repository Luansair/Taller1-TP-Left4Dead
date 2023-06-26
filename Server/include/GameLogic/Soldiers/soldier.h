#ifndef SOLDIER_H_
#define SOLDIER_H_

#include "../Weapons/weapon.h"
#include "../position.h"
#include "../hitbox.h"
#include "../radialhitbox.h"
#include "../../../../Common/include/Information/information_code.h"

#include <map>
#include <memory>
#include <chrono>
#include <iostream>

class Zombie;
class Throwable;
class ThrowableFactory;

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
    int8_t dir_x = RIGHT;
    uint8_t t_type;
    double revive_radius, revive_cooldown, reload_cooldown, throw_cooldown, throw_duration;
    double damage_recv = 0.0;
    uint16_t kill_counter = 0;
    double actual_health = health;

    /* tiempos */
    std::chrono::_V2::system_clock::time_point last_step_time = std::chrono::system_clock::now();
    std::chrono::_V2::system_clock::time_point born_time = std::chrono::system_clock::now();
    std::chrono::_V2::system_clock::time_point death_time = std::chrono::system_clock::now();
    std::chrono::_V2::system_clock::time_point reload_time = std::chrono::system_clock::now();
    std::chrono::_V2::system_clock::time_point being_hurt_time = std::chrono::system_clock::now();
    std::chrono::_V2::system_clock::time_point throw_time = std::chrono::system_clock::now();
    std::chrono::_V2::system_clock::time_point last_throw_time = std::chrono::system_clock::now();

    /* estados */
    bool dying = false;
    bool moving = false;
    bool shooting = false;
    bool reloading = false;
    bool throwing = false;
    bool reviving = false;
    bool being_hurt = false;
    bool alive = true;
    bool throwed = false;
    bool changing = false;

    explicit Soldier(
    uint32_t soldier_id,
    double width,
    double height,
    double speed,
    double health,
    std::unique_ptr<Weapon>&& weapon,
    uint8_t t_type,
    double revive_radius,
    double revive_cooldown,
    double reload_cooldown,
    double throw_cooldown,
    double throw_duration);

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
    virtual void recvDamage(uint8_t state, double damage);
    virtual void start_dying(uint8_t state);
    virtual void start_throw(uint8_t state);
    virtual void revive(uint8_t state);
    virtual void be_revived(void);
    virtual void keep_reloading(uint8_t state);
    void increase_kill_counter(void);
    virtual void change_grenade_type(uint8_t state);

    /* SIMULADORES */

    virtual void simulate(std::chrono::_V2::system_clock::time_point real_time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies, 
    std::map<uint32_t, std::shared_ptr<Throwable>>& throwables, double dim_x, double dim_y, ThrowableFactory& factory);
    virtual void simulateMove(double time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies, double dim_x, double dim_y);
    virtual void simulateShoot(std::chrono::_V2::system_clock::time_point real_time, double time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies,
    double dim_x);
    virtual void simulateReload(std::chrono::_V2::system_clock::time_point real_time);
    virtual void simulateThrow(std::chrono::_V2::system_clock::time_point real_time, double dim_x, double dim_y,
    std::map<uint32_t, std::shared_ptr<Throwable>>& throwables, ThrowableFactory& factory);
    virtual void simulateDie(std::chrono::_V2::system_clock::time_point real_time);
    virtual void simulateRevive(std::chrono::_V2::system_clock::time_point real_time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers);
    virtual void simulateRecvdmg(std::chrono::_V2::system_clock::time_point real_time);
    virtual void simulate_change_grenade(void); 

    /* GETTERS */

    int8_t getDir();
    int8_t getDirX();
    double getHealth();
    double getActualHealth();
    double getWidth();
    double getHeight();
    uint32_t getId();
    virtual uint8_t getSoldierType() = 0;
    virtual uint8_t getAction() = 0;
    Position& getPosition();
    [[nodiscard]] const Position& seePosition() const;
    bool isDead(void);
    uint16_t getKills(void);
    double secondsAlive(void);
    uint16_t getAmmo(void);
    uint16_t getActualAmmo(void);
    double getTimeLeft(void);
    uint8_t isDeadFeedback(void);
    uint32_t getBulletsFired(void);

    /* SETTERS */

    void setPosition(Position&& new_pos);
    void setRandomPosition(
            const std::map<uint32_t, std::shared_ptr<Soldier>> &soldiers,
            const std::map<uint32_t, std::shared_ptr<Zombie>> &zombies, double dim_x, double dim_y);
};

#endif  // SOLDIER_H_
