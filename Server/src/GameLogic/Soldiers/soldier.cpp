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
    
    if (dying) return;
    switch(state) {
        case ON:
            moving = true;
            // si quisiera seguir recargando -> no cancelar reloading
            reloading = shooting = throwing = reviving = being_hurt = false;
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
    if (dying) return;
    switch(state) {
        case ON:
            if (reloading) return;
            shooting = true;
            moving = reloading = throwing = reviving = being_hurt = false;
            break;
        case OFF:
            shooting = false;
            break;
    }
}

void Soldier::reload(uint8_t state, std::chrono::_V2::steady_clock::time_point reload_start_time) {
    if (dying) return;
    switch(state) {
        case ON:
            if (reloading) return;
            reloading = true;
            reload_time = reload_start_time;
            // si quisiera moverme al mismo tiempo -> sacar moving
            moving = shooting = throwing = reviving = being_hurt = false;
            break;
        case OFF:
            reloading = false;
            break;
    }
}

void Soldier::throwGrenade(uint8_t state){
    if (dying) return;
    switch(state) {
        case ON:
            throwing = true;
            moving = shooting = reloading = reviving = being_hurt = false;
            break;
        case OFF:
            throwing = false;
            break;
    }
}

void Soldier::recvDamage(uint8_t state, double damage, std::chrono::_V2::steady_clock::time_point recvdmg_start_time) {
    if (dying) return;
    switch(state) {
        case ON:
            reloading = shooting = throwing = reviving = false;
            being_hurt = true;
            being_hurt_time = recvdmg_start_time;
            damage_recv = damage;
            break;
        case OFF:
            being_hurt = false;
            break;
    }
}

void Soldier::idle(uint8_t state) {
    // si quisiera disparar y moverme al mismo tiempo:
    // if (reloading && !moving) return;
    // if (reloading && moving) {
    //     switch(state) {
    //         case ON:
    //             shooting = moving = throwing = reviving = being_hurt = false;
    //             break;
    //         case OFF:
    //             break;
    //     }
    //     return;       
    // }
    if (reloading) return;
    switch(state) {
        case ON:
            reloading = shooting = moving = throwing = reviving = being_hurt = false;
            break;
        case OFF:
            break;
    }
}

void Soldier::die(uint8_t state, std::chrono::_V2::steady_clock::time_point death_start_time) {
    switch(state) {
        case ON:
            if (dying) return;
            death_time = death_start_time;
            shooting = moving = throwing = being_hurt = reloading = reviving = false;
            dying = true;
            break;
        case OFF:
            dying = false;
            break;
    }
}

void Soldier::revive(uint8_t state) {
    if (dying) return;
    switch(state) {
        case ON:
            shooting = moving = throwing = reloading = being_hurt = false;
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

void Soldier::simulate(double time, std::chrono::_V2::steady_clock::time_point real_time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies, double dim_x, double dim_y) {
    
    // calculo el tiempo que lleva muriendo o recargando
    std::chrono::duration<double> time_reloading = real_time - reload_time;
    std::chrono::duration<double> time_dying = real_time - death_time;

    // si está muriendo y el tiempo para revivirlo terminó, se muere.
    if (dying && (time_dying.count() > revive_cooldown)) simulateDie(real_time);

    // si está muriendo y el tiempo para revivirlo no terminó, se sigue muriendo.
    if (dying && (time_dying.count() <= revive_cooldown)) {
        return;
    }

    // si está recargando y el tiempo de recarga no terminó, sigue recargando.
    if (reloading && (time_reloading.count() <= reload_cooldown)) {
        // si quisiera mover y recargar al mismo tiempo:
        // if (moving) simulateMove(time, real_time, soldiers, zombies, dim_x, dim_y);
        return;
    }

    // si está recargando y ya pasó el tiempo de recarga, termina de recargar.
    if (reloading && (time_reloading.count() > reload_cooldown)) simulateReload(real_time);

    // simulo el resto de las acciones.
    if (moving) simulateMove(time, real_time, soldiers, zombies, dim_x, dim_y);
    if (being_hurt) simulateRecvdmg(real_time);
    if (shooting) simulateShoot(time, real_time, soldiers, zombies, dim_x);
    if (throwing) simulateThrow(time, real_time);
    if (reviving) simulateRevive(time, real_time, soldiers);
}

void Soldier::simulateRecvdmg(std::chrono::_V2::steady_clock::time_point real_time) {
    if (dying) return;
    if (damage_recv < health) {
        health -= damage_recv; 
        return;
    }
    die(ON, being_hurt_time);
}

void Soldier::simulateRevive(double time, std::chrono::_V2::steady_clock::time_point real_time,
std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers) {

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

void Soldier::simulateDie(std::chrono::_V2::steady_clock::time_point real_time) {
    alive = false;
}

void Soldier::simulateMove(double time,
    std::chrono::_V2::steady_clock::time_point real_time,
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

void Soldier::simulateShoot(double time, std::chrono::_V2::steady_clock::time_point real_time, 
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies, double dim_x) {
    if (!(weapon->shoot(getPosition(), dir, dim_x, time, real_time, std::ref(soldiers), std::ref(zombies)))) reload(ON, real_time);
}

void Soldier::simulateReload(std::chrono::_V2::steady_clock::time_point real_time) {
    weapon->reload();
    reload(OFF, real_time);
}

void Soldier::simulateThrow(double time, std::chrono::_V2::steady_clock::time_point real_time) {}

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