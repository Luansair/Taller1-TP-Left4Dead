#ifndef ZOMBIE_H_
#define ZOMBIE_H_

#include "../position.h"
#include "../hitbox.h"
#include "../../../../Common/include/Information/information_code.h"
#include "../../../include/GameLogic/Soldiers/soldier.h"

#include <utility>
#include <cstdint>
#include <map>
#include <memory>

class Zombie {
public:
    uint32_t zombie_id;
    int8_t dir;
    uint8_t axis = 0;
    int8_t speed;
    int16_t health;
    int8_t width;
    int8_t height;
    Position position;
    int8_t dir_x = RIGHT;
    bool moving = false;
    bool attacking = false;
    bool alive = true;

    virtual ~Zombie() {}

    explicit Zombie(
    uint32_t zombie_id,
    int8_t dir,
    int8_t width,
    int8_t height,
    int8_t speed,
    int16_t health);

    /* COMANDOS */

    virtual void move(
    uint8_t state,
    uint8_t moveAxis,
    int8_t moveDirection,
    uint8_t moveForce);
    virtual void attack(uint8_t state);
    virtual void idle(uint8_t state);
    virtual void recvDamage(int8_t damage);

    /* SIMULADORES */

    virtual void simulate(uint16_t time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies, int32_t dim_x, int32_t dim_y);
    virtual void simulateMove(uint16_t time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies, int32_t dim_x, int32_t dim_y);
    virtual void simulateAttack(uint16_t time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies,
    int32_t dim_x);

    /* GETTERS */

    int8_t getDir(void);
    int8_t getDirX(void);
    int8_t getHealth(void);
    uint8_t getWidth(void);
    uint8_t getHeight(void);
    uint32_t getId(void);
    virtual uint8_t getSoldierType(void) = 0;
    uint8_t getAction(void);
    Position& getPosition(void);
    const Position& seePosition(void) const;

    /* SETTERS */

    void setPosition(Position&& new_pos);
    void setRandomPosition(
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies, int32_t dim_x, int32_t dim_y);

};

#endif  // ZOMBIE_H_
