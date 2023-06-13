#include "../../../include/GameLogic/Zombies/zombie.h"
#include <random>

/* CONSTRUCTOR */

Zombie::Zombie(
    uint32_t zombie_id,
    int8_t dir,
    int8_t width,
    int8_t height,
    int8_t speed,
    int16_t health) :
    zombie_id(zombie_id),
    dir(dir),
    speed(speed),
    health(health),
    width(width),
    height(height),
    position() {
}

/* COMANDOS */

void Zombie::move(
    uint8_t state,
    uint8_t moveAxis,
    int8_t moveDirection,
    uint8_t moveForce) {

    switch(state) {
        case ON:
            moving = true;
            attacking = false;
            axis = moveAxis;
            dir = moveDirection;
            speed = moveForce;
            if (moveAxis == X) dir_x = moveDirection;
            break;
        case OFF:
            moving = false;
            break;
    }
}

void Zombie::attack(uint8_t state) {
    switch(state) {
        case ON:
            attacking = true;
            moving = false;
            break;
        case OFF:
            attacking = false;
            break;
    }
}

void Zombie::idle(uint8_t state) {
    switch(state) {
        case ON:
            moving = attacking = false;
            break;
        case OFF:
            break;
    }
}

void Zombie::recvDamage(int8_t damage) {
    if (damage < health) {
        health -= damage; 
        return;
    }
    alive = false;
}

/* SIMULADORES */

void Zombie::simulate(uint16_t time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies, int32_t dim_x, int32_t dim_y) {
    if (moving) simulateMove(time, soldiers, zombies, dim_x, dim_y);
    if (attacking) simulateAttack(time, soldiers, zombies, dim_x);
}

void Zombie::simulateMove(uint16_t time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies, int32_t dim_x, int32_t dim_y) {

    int16_t next_x;
    int16_t next_y;

    // calculo proxima coordenada.
    switch(axis) {
        case X:
            next_x = position.getXPos() + (dir * speed * time);
            next_y = position.getYPos();
            if (next_x < 0) next_x = dim_x + next_x;
            if (next_x > dim_x) next_x = next_x - dim_x;
            break;
        case Y:
            next_y = position.getYPos() + (dir * speed * time);
            next_x = position.getXPos();
            if (next_y < 0) next_y = dim_y + next_y;
            if (next_y > dim_y) next_y = next_y - dim_y;
            break;
    }
    Position next_pos(next_x, next_y, position.getWidth(), position.getHeight(), dim_x, dim_y);

    // verifico las colisiones.
    for (auto i = soldiers.begin(); i != soldiers.end(); i++) {
        Position other_pos = i->second->getPosition();
        if (next_pos.collides(other_pos)) {
            return;
        }
    }
    // lo mismo con los zombies
    for (auto i = zombies.begin(); i != zombies.end(); i++) {
        Position other_pos = i->second->getPosition();
        if (i->second->getId() == zombie_id) continue;
        if (next_pos.collides(other_pos)) {
            return;
        }
    }
    // si no colisiono cambio de pos
    position = next_pos;
}

void Zombie::simulateAttack(uint16_t time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies,
    int32_t dim_x) {}

/* GETTERS */

uint8_t Zombie::getWidth(void) {
    return width;
}
uint8_t Zombie::getHeight(void) {
    return height;
}

uint32_t Zombie::getId(void) {
    return zombie_id;
}

uint8_t Zombie::getAction(void) {
    if (moving) return ACTION_MOVE;
    // if (attacking) return ACTION_ATTACK;
    return ACTION_IDLE;
}

int8_t Zombie::getDir(void) {
    return dir;
}

int8_t Zombie::getDirX(void) {
    return dir_x;
}

int8_t Zombie::getHealth(void) {
    return health;
}

Position& Zombie::getPosition(void) {
    return std::ref(position);
}

const Position& Zombie::seePosition(void) const {
    return std::ref(position);
}

/* SETTERS */

void Zombie::setPosition(Position&& new_pos) {
    position = new_pos;
}

void Zombie::setRandomPosition(
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies, int32_t dim_x, int32_t dim_y) {
    using std::random_device;
    using std::mt19937;
    using std::uniform_int_distribution;
    using std::uint32_t;

    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int32_t> distx(0, dim_x);
    uniform_int_distribution<int32_t> disty(0, dim_y);
    int32_t x_pos;
    int32_t y_pos;
    bool collides;
    do {
        collides = false;
        x_pos = distx(mt);
        y_pos = disty(mt);
        Position position(x_pos, y_pos, getWidth(), getHeight(), dim_x, dim_y);
        for (auto i = soldiers.begin(); i != soldiers.end(); i++) {
            Position other_pos = i->second->getPosition();
            if (position.collides(other_pos)) {
                collides = true;
                break;
            }
        }
    } while (collides);
    Position position(x_pos, y_pos, getWidth(), getHeight(), dim_x, dim_y);
    setPosition(std::move(position));
}