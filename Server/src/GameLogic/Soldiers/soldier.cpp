#include "../../../include/GameLogic/Soldiers/soldier.h"
#include <random>
#include <tuple>

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
    
    if (dying) return; //esta linea es para que se quede totalmente quieto cuando está en el suelo.
    switch(state) {
        case ON:
            moving = true;
            reloading = shooting = throwing = reviving = being_hurt = false;
            axis = moveAxis;
            dir = moveDirection;
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
            if (reloading) return;
            shooting = true;
            moving = reloading = throwing = reviving = being_hurt = false;
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
            moving = shooting = throwing = reviving = being_hurt = false;
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
            moving = shooting = reloading = reviving = being_hurt = false;
            break;
        case OFF:
            throwing = false;
            break;
    }
}

void Soldier::recvDamage(uint8_t state, double damage) {
    switch(state) {
        case ON:
            reloading = shooting = throwing = reviving = false;
            being_hurt = true;
            damage_recv = damage;
            break;
        case OFF:
            being_hurt = false;
            break;
    }
}

void Soldier::start_dying(uint8_t state) {
    switch(state) {
        case ON:
            shooting = moving = throwing = being_hurt = reloading = reviving = false;
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
            shooting = moving = throwing = reloading = being_hurt = false;
            reviving = true;
            break;
        case OFF:
            reviving = false;
            break;
    }
}

void Soldier::keep_reloading(uint8_t state) {
    switch(state) {
        case ON:
            shooting = moving = throwing = reviving = being_hurt = false;
            break;
        case OFF:
            break;
    }
}

void Soldier::idle(uint8_t state) {
    switch(state) {
        case ON:
            reloading = shooting = moving = throwing = reviving = being_hurt = false;
            break;
        case OFF:
            break;
    }
}

void Soldier::be_revived(void) {
    start_dying(OFF);
    health = 100;
}

void Soldier::increase_kill_counter(void) {
    kill_counter += 1;
}

/* SIMULADORES */

void Soldier::simulate(std::chrono::_V2::steady_clock::time_point real_time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies, double dim_x, double dim_y) {

    std::chrono::duration<double> time = real_time - last_step_time;

    if (dying) simulateDie(real_time);
    if (being_hurt) simulateRecvdmg(real_time);
    if (reloading) simulateReload(real_time);
    if (shooting) simulateShoot(real_time, time.count(), soldiers, zombies, dim_x);
    if (moving) simulateMove(time.count(), soldiers, zombies, dim_x, dim_y);
    if (throwing) simulateThrow(real_time);
    if (reviving) simulateRevive(real_time, soldiers);
    last_step_time = real_time;
}

void Soldier::simulateRecvdmg(std::chrono::_V2::steady_clock::time_point real_time) {
    if (damage_recv < health) {
        health -= damage_recv;
        recvDamage(OFF, 0);
        return;
    }
    // si muere, le seteo el tiempo de muerte y ejecuto el comando die.
    death_time = real_time;
    start_dying(ON);
}

void Soldier::simulateRevive(std::chrono::_V2::steady_clock::time_point real_time,
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
    std::chrono::duration<double> time_dying = real_time - death_time;
    // si tiempo para revivirlo terminó, se muere.
    idle(ON);
    if (time_dying.count() > revive_cooldown) alive = false;
}

void Soldier::simulateMove(
    double time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies, double dim_x, double dim_y) {
    // calculo proxima coordenada.
    std::tuple<double, double> next_coords = position.calculateNextPos(axis, dir, speed, time);
    Position next_pos(std::get<0>(next_coords), std::get<1>(next_coords), position.getWidth(), position.getHeight(), dim_x, dim_y);

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

void Soldier::simulateShoot(std::chrono::_V2::steady_clock::time_point real_time, double time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies, double dim_x) {
    if (!(weapon->shoot(
        getPosition(), dir, dim_x, time, 
        std::ref(soldiers), std::ref(zombies)))) {
            
            reload_time = real_time;
            reload(ON);
    }
}

void Soldier::simulateReload(std::chrono::_V2::steady_clock::time_point real_time) {
    std::chrono::duration<double> time_reloading = real_time - reload_time;
    if (time_reloading.count() > reload_cooldown) {
        weapon->reload();
        reload(OFF);
    }
    keep_reloading(ON);
}

void Soldier::simulateThrow(std::chrono::_V2::steady_clock::time_point real_time) {}

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

uint16_t Soldier::getKills(void) {
    return kill_counter;
}

double Soldier::secondsAlive(void) {
    std::chrono::duration<double> time_alive = last_step_time - born_time;
    return time_alive.count();
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