#include "../../../include/GameLogic/Zombies/zombie.h"
#include <random>
#include<cmath>

/* CONSTRUCTOR */

Zombie::Zombie(
    uint32_t zombie_id,
    double width,
    double height,
    double speed,
    double health) :
    zombie_id(zombie_id),
    speed(speed),
    health(health),
    width(width),
    height(height),
    position(0,0,width,height,0,0) {
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

void Zombie::recvDamage(double damage) {
    if (damage < health) {
        health -= damage; 
        return;
    }
    alive = false;
}

/* SIMULADORES */

void Zombie::simulate(double time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies, double dim_x, double dim_y) {
    simulateMove(time, soldiers, zombies, dim_x, dim_y);
    if (attacking) simulateAttack(time, soldiers, zombies, dim_x);
}

void Zombie::simulateMove(double time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies, double dim_x, double dim_y) {

    // calculo la zona de visión del zombie.
    Position sight_zone(position.getXPos(), position.getYPos(), sight, sight, dim_x, dim_y);
    Position next_pos(position.getXPos(), position.getYPos(), position.getWidth(), position.getHeight(), dim_x, dim_y);

    // verifico las colisiones.
    double distance = std::sqrt(std::pow(dim_x, 2) + std::pow(dim_y, 2)); // distancia maxima
    double new_distance;
    double m;
    double b;
    double next_x;
    bool collision = false;
    for (auto i = soldiers.begin(); i != soldiers.end(); i++) {
        Position other_pos = i->second->getPosition();
        if (sight_zone.collides(other_pos)) {
            new_distance = std::sqrt(std::pow(std::abs(sight_zone.getXPos() - other_pos.getXPos()), 2) + std::pow(std::abs(sight_zone.getYPos() - other_pos.getYPos()), 2));
            if (distance > new_distance) {
                distance = new_distance;
                m = (sight_zone.getYPos() - other_pos.getYPos()) / (sight_zone.getXPos() - other_pos.getXPos());
                b = sight_zone.getYPos() - m * sight_zone.getXPos();
                // me tengo que quedar con el más cercano
                next_x = other_pos.getXPos();
            }
            collision = true;
        }
    }

    if (collision) {

        if (sight_zone.getXPos() > next_x) {
            position.setXPos(sight_zone.getXPos() - ((sight_zone.getXPos() - next_x) * 0.006));
            dir = RIGHT;
        } else {
            position.setXPos(sight_zone.getXPos() + ((next_x - sight_zone.getXPos()) * 0.006));
            dir = LEFT;
        }
        position.setYPos(position.getXPos() * m + b);
        moving = true;
    } else {
        moving = false;
    }

}

void Zombie::simulateAttack(double time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies,
    double dim_x) {}

/* GETTERS */

double Zombie::getWidth(void) {
    return width;
}
double Zombie::getHeight(void) {
    return height;
}

uint32_t Zombie::getId(void) {
    return zombie_id;
}

uint8_t Zombie::getAction(void) {
    if (moving) return ACTION_MOVE;
    // if (attacking) return ACTION_ATTACK;
    return ZOMBIE_IDLE;
}

int8_t Zombie::getDir(void) {
    return dir;
}

int8_t Zombie::getDirX(void) {
    return dir_x;
}

double Zombie::getHealth(void) {
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
        const std::map<uint32_t, std::shared_ptr<Soldier>> &soldiers,
        const std::map<uint32_t, std::shared_ptr<Zombie>> &zombies, double dim_x, double dim_y) {
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
        Position _position(x_pos, y_pos, getWidth(), getHeight(), dim_x, dim_y);
        for (auto i = soldiers.begin(); i != soldiers.end(); i++) {
            Position other_pos = i->second->getPosition();
            if (position.collides(other_pos)) {
                collides = true;
                break;
            }
        }
    } while (collides);
    Position _position(x_pos, y_pos, getWidth(), getHeight(), dim_x, dim_y);
    setPosition(std::move(_position));
}
