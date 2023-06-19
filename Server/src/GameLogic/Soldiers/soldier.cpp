#include "../../../include/GameLogic/Soldiers/soldier.h"
#include <random>

/* CONSTRUCTOR */

Soldier::Soldier(
    uint32_t soldier_id,
    double width,
    double height,
    double speed,
    double health,
    std::unique_ptr<Weapon>&& weapon,
    std::unique_ptr<Grenade>&& grenade) :
    soldier_id(soldier_id),
    speed(speed),
    health(health),
    width(width),
    height(height),
    position(0,0,width,height,0,0),
    weapon(std::move(weapon)),
    grenade(std::move(grenade)) {
}

/* COMANDOS */

void Soldier::move(
    uint8_t state,
    uint8_t moveAxis,
    int8_t moveDirection,
    uint8_t moveForce) {

    switch(state) {
        case ON:
            moving = true;
            shooting = reloading = throwing = false;
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

void Soldier::shoot(uint8_t state) {
    switch(state) {
        case ON:
            shooting = true;
            moving = reloading = throwing = false;
            break;
        case OFF:
            shooting = false;
            break;
    }
}

void Soldier::reload(uint8_t state) {
    switch(state) {
        case ON:
            reloading = true;
            moving = shooting = throwing = false;
            break;
        case OFF:
            reloading = false;
            break;
    }
}

void Soldier::throwGrenade(uint8_t state){
    switch(state) {
        case ON:
            throwing = true;
            moving = shooting = reloading = false;
            break;
        case OFF:
            throwing = false;
            break;
    }
}

void Soldier::idle(uint8_t state) {
    switch(state) {
        case ON:
            reloading = shooting = moving = throwing = false;
            break;
        case OFF:
            break;
    }
}

void Soldier::recvDamage(double damage) {
    if (dying) return;
    if (damage < health) {
        health -= damage; 
        return;
    }
    die(ON);
}

void Soldier::die(uint8_t state) {
    switch(state) {
        case ON:
            counter = 10000;
            shooting = moving = throwing = false;
            dying = true;
            break;
        case OFF:
            dying = false;
            break;
    }
}

void Soldier::revive(uint8_t state) {
    switch(state) {
        case ON:
            shooting = moving = throwing = false;
            reviving = true;
            break;
        case OFF:
            reviving = false;
            break;
    }
}

void Soldier::be_revived(void) {
    dying = false;
    health = 100;
}

/* SIMULADORES */

void Soldier::simulate(double time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies, double dim_x, double dim_y) {
    if (dying && (counter < 0)) simulateDie();
    counter = counter - 1;
    if (dying) return;
    if (moving) simulateMove(time, soldiers, zombies, dim_x, dim_y);
    if (reloading) simulateReload(time);
    if (shooting) simulateShoot(time, soldiers, zombies, dim_x);
    if (throwing) simulateThrow(time);
    if (reviving) simulateRevive(time, soldiers);
}

void Soldier::simulateRevive(double time, std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers) {
        // verifico las colisiones.
    
    RadialHitbox revive_zone(position.getXPos(), position.getYPos(), revive_radius);
    for (auto i = soldiers.begin(); i != soldiers.end(); i++) {
        Position other_pos = i->second->getPosition();
        if (i->second->getId() == soldier_id) continue;
        if (revive_zone.hits(other_pos)) {
            if (i->second->dying) {
                i->second->be_revived();
            }
        }
    }
}

void Soldier::simulateDie(void) {
    alive = false;
}

void Soldier::simulateMove(double time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies, double dim_x, double dim_y) {

    double next_x;
    double next_y;

    // calculo proxima coordenada.
    switch(axis) {
        case X:
            next_x = position.getXPos() + (dir * speed * time);
            next_y = position.getYPos();
            if (next_x < 0) next_x = dim_x + next_x + 1.0;
            if (next_x > dim_x) next_x = next_x - dim_x - 1.0;
            break;
        case Y:
            next_y = position.getYPos() + (dir * speed * time);
            next_x = position.getXPos();
            if (next_y < 0) next_y = dim_y + next_y + 1.0;
            if (next_y > dim_y) next_y = next_y - dim_y - 1.0;
            break;
    }
    Position next_pos(next_x, next_y, position.getWidth(), position.getHeight(), dim_x, dim_y);

    // verifico las colisiones.
    for (auto i = soldiers.begin(); i != soldiers.end(); i++) {
        Position other_pos = i->second->getPosition();
        if (i->second->getId() == soldier_id) continue;
        if (next_pos.collides(other_pos)) {
            return;
        }
    }
    // lo mismo con los zombies
    for (auto i = zombies.begin(); i != zombies.end(); i++) {
        Position other_pos = i->second->getPosition();
        if (next_pos.collides(other_pos)) {
            return;
        }
    }

    // si no colisiono cambio de pos
    position = next_pos;
}

void Soldier::simulateShoot(double time, 
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies, double dim_x) {
    if (!(weapon->shoot(getPosition(), dir, dim_x, time, std::ref(soldiers), std::ref(zombies)))) reload(ON);
}

void Soldier::simulateReload(double time) {
    (weapon->reload());
}

void Soldier::simulateThrow(double time) {}

/* GETTERS */

bool Soldier::isDead(void) {
    return (!alive);
}

double Soldier::getWidth(void) {
    return width;
}
double Soldier::getHeight(void) {
    return height;
}

uint32_t Soldier::getId(void) {
    return soldier_id;
}

int8_t Soldier::getDir(void) {
    return dir;
}

int8_t Soldier::getDirX(void) {
    return dir_x;
}

double Soldier::getHealth(void) {
    return health;
}

Position& Soldier::getPosition(void) {
    return std::ref(position);
}

const Position& Soldier::seePosition(void) const {
    return std::ref(position);
}

/* SETTERS */

void Soldier::setPosition(Position&& new_pos) {
    position = new_pos;
}

void Soldier::setRandomPosition(
        const std::map<uint32_t, std::shared_ptr<Soldier>> &soldiers,
        const std::map<uint32_t, std::shared_ptr<Zombie>> &zombies, double dim_x, double dim_y) {
    using std::random_device;
    using std::mt19937;
    using std::uniform_int_distribution;
    using std::uint32_t;

    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int32_t> distx(0, dim_x * 0.5);
    uniform_int_distribution<int32_t> disty(0, dim_y);
    int32_t x_pos;
    int32_t y_pos;
    bool collides;
    do {
        collides = false;
        x_pos = distx(mt);
        y_pos = disty(mt);
        Position _position(x_pos, y_pos, getWidth(), getHeight(), dim_x, dim_y);
        for (const auto & soldier : soldiers) {
            Position other_pos = soldier.second->getPosition();
            if (_position.collides(other_pos)) {
                collides = true;
                break;
            }
        }
    } while (collides);
    Position _position(x_pos, y_pos, getWidth(), getHeight(), dim_x, dim_y);
    setPosition(std::move(_position));
}