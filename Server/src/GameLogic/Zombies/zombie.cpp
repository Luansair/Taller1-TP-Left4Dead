#include "../../../include/GameLogic/Zombies/zombie.h"
#include "../../../include/GameLogic/Soldiers/soldier.h"
#include "../../../include/GameLogic/Throwables/throwablesfactory.h"
#include "../../../include/GameLogic/Throwables/throwable.h"
#define SPAWNRANGE 1000

/* CONSTRUCTOR */

Zombie::Zombie(
    uint32_t zombie_id,
    double width,
    double height,
    double speed,
    double health,
    double sight,
    double listening_range,
    double hit_scope,
    double damage,
    double die_cooldown,
    double stunned_cooldown) :
    zombie_id(zombie_id),
    speed(speed),
    health(health),
    width(width),
    height(height),
    position(0,0,width,height,0,0),
    att_vic(nullptr),
    sight(sight),
    listening_range(listening_range),
    hit_scope(hit_scope),
    damage(damage),
    die_cooldown(die_cooldown),
    stunned_cooldown(stunned_cooldown) {
}

/* COMANDOS */

void Zombie::move(
    uint8_t state,
    int8_t moveDirection) {

    switch(state) {
        case ON:
            moving = true;
            attacking = being_hurt = screaming = false;
            dir = moveDirection;
            dir_x = moveDirection;
            break;
        case OFF:
            dir_x = moveDirection;
            moving = false;
            break;
    }
}

void Zombie::attack(uint8_t state, std::shared_ptr<Soldier> victim) {
    switch(state) {
        case ON:
            attacking = true;
            att_vic = victim;
            moving = being_hurt = screaming = false;
            break;
        case OFF:
            attacking = false;
            att_vic = victim;
            break;
    }
}

void Zombie::die(uint8_t state) {
    switch(state) {
        case ON:
            attacking = moving = being_hurt = screaming = false;
            dying = true;
            break;
        case OFF:
            dying = false;
            break;
    }
}


void Zombie::be_stunned(uint8_t state) {
    switch(state) {
        case ON:
            is_stunned = true;
            attacking = moving = being_hurt = screaming = false;
            break;
        case OFF:
            is_stunned = false;
            break;
    }
}

void Zombie::idle(uint8_t state) {
    switch(state) {
        case ON:
            moving = attacking = being_hurt = screaming = false;
            break;
        case OFF:
            break;
    }
}

void Zombie::recvDamage(uint8_t state, double damage, uint32_t attacker) {
    switch(state) {
        case ON:
            moving = attacking = screaming = false;
            being_hurt = true;
            damage_recv = damage;
            attacker_id = attacker;
            break;
        case OFF:
            being_hurt = false;
            break;
    }
}


/* SIMULADORES */

void Zombie::simulate(std::chrono::_V2::system_clock::time_point real_time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies, 
    std::map<uint32_t, std::shared_ptr<Throwable>>& throwables, double dim_x, double dim_y, ThrowableFactory& factory) {
    if (dying) { simulateDie(real_time); last_step_time = real_time; return; }
    if (is_stunned) simulateStunned(real_time);
    if (being_hurt) simulateRecvDamage(real_time, soldiers);
    if (attacking) simulateAttack();
    if (!is_stunned) simulateMove(real_time, soldiers, zombies, throwables, dim_x, dim_y, factory);
    last_step_time = real_time;
}

void Zombie::simulateStunned(std::chrono::_V2::system_clock::time_point real_time) {

    if (!stunned) {
        stunned_time = real_time;
        stunned = true;
    } else {
        std::chrono::duration<double> time = real_time - stunned_time;
        if (time.count() > stunned_cooldown) {
            be_stunned(OFF);
            stunned = false;
        }
    }
}

void Zombie::simulateRecvDamage(
    std::chrono::_V2::system_clock::time_point real_time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers) {
    if (damage_recv < actual_health) {
        actual_health -= damage_recv; 
        recvDamage(OFF, 0, attacker_id);
        return;
    }
    death_time = real_time;
    die(ON);
    soldiers.at(attacker_id)->increase_kill_counter();
}

void Zombie::simulateDie(std::chrono::_V2::system_clock::time_point real_time) {
    std::chrono::duration<double> time_dying = real_time - death_time;
    if (time_dying.count() > die_cooldown) alive = false;
    idle(ON);
}

void Zombie::detect_victim(
    bool *detected, 
    uint32_t *victim,
    std::map<uint32_t, 
    std::shared_ptr<Soldier>>& soldiers, 
    double dim_x, 
    double dim_y) {

    RadialHitbox sight_zone(position.getXPos(), position.getYPos(), sight);

    // verifico las colisiones.
    double distance = std::sqrt(std::pow(dim_x, 2) + std::pow(dim_y, 2)); // distancia maxima
    double new_distance;
    for (auto i = soldiers.begin(); i != soldiers.end(); i++) {
        Position other_pos = i->second->getPosition();
        if (sight_zone.hits(other_pos) && !(i->second->isDying()) && !(i->second->isDead())) {
            new_distance = std::sqrt(std::pow(std::abs(position.getXPos() - other_pos.getXPos()), 2) + std::pow(std::abs(position.getYPos() - other_pos.getYPos()), 2));
            if (distance > new_distance) {
                distance = new_distance;
                // me tengo que quedar con el más cercano
                *victim = i->first;
            }
            *detected = true;
        }
    }
}

void Zombie::detect_screaming_witch(
    bool *detected, 
    uint32_t *witch_id,
    std::map<uint32_t, 
    std::shared_ptr<Zombie>>& zombies, 
    double dim_x, 
    double dim_y) {

    RadialHitbox listening_zone(position.getXPos(), position.getYPos(), listening_range);

    // verifico las colisiones.
    double distance = std::sqrt(std::pow(dim_x, 2) + std::pow(dim_y, 2)); // distancia maxima
    double new_distance;
    for (auto i = zombies.begin(); i != zombies.end(); i++) {
        Position other_pos = i->second->getPosition();
        if (listening_zone.hits(other_pos) && (i->second->screaming)) {
            new_distance = std::sqrt(std::pow(std::abs(position.getXPos() - other_pos.getXPos()), 2) + std::pow(std::abs(position.getYPos() - other_pos.getYPos()), 2));
            if (distance > new_distance) {
                distance = new_distance;
                // me tengo que quedar con el más cercano
                *witch_id = i->first;
            }
            *detected = true;
        }
    }
}

void Zombie::CalculateNextPos_by_victim(double *next_x, double *next_y, 
    int8_t *direction, uint32_t victim_id, std::map<uint32_t, 
    std::shared_ptr<Soldier>>& soldiers, double time) {

    std::shared_ptr<Soldier> &victim = soldiers.at(victim_id);
    double target_x = victim->getPosition().getXPos();
    double target_y = victim->getPosition().getYPos();
    double x = position.getXPos();
    double y = position.getYPos();
    if (target_x - x < 0) {
        target_x += victim->getWidth();
        *direction = LEFT;
    } else {
        *direction = RIGHT;
        target_y += victim->getWidth();
    }
    if (target_y - y < 0) {
        target_y += victim->getHeight();
    } else {
        target_y += victim->getHeight();
    }
    double norma = std::sqrt(std::pow(std::abs(target_x - x), 2) + std::pow(std::abs(target_y - y), 2));
    *next_x = ((target_x - x) / norma) * time * speed + x;
    *next_y = ((target_y - y) / norma) * time * speed + y;
}

void Zombie::CalculateNextPos_by_witch(double *next_x, double *next_y, 
    int8_t *direction, uint32_t witch_id, std::map<uint32_t, 
    std::shared_ptr<Zombie>>& zombies, double time) {

    std::shared_ptr<Zombie> &witch = zombies.at(witch_id);
    double target_x = witch->getPosition().getXPos();
    double target_y = witch->getPosition().getYPos();
    double x = position.getXPos();
    double y = position.getYPos();
    if (target_x - x < 0) {
        target_x += witch->getWidth();
        *direction = LEFT;
    } else {
        *direction = RIGHT;
        target_y += witch->getWidth();
    }
    if (target_y - y < 0) {
        target_y += witch->getHeight();
    } else {
        target_y += witch->getHeight();
    }
    double norma = std::sqrt(std::pow(std::abs(target_x - x), 2) + std::pow(std::abs(target_y - y), 2));
    *next_x = ((target_x - x) / norma) * time * speed + x;
    *next_y = ((target_y - y) / norma) * time * speed + y;
}

void Zombie::simulateMove(std::chrono::_V2::system_clock::time_point real_time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies, 
    std::map<uint32_t, std::shared_ptr<Throwable>>& throwables, double dim_x, double dim_y, ThrowableFactory& factory) {
    std::chrono::duration<double> time = real_time - last_step_time;

    bool detected = false;
    uint32_t id;
    
    detect_victim(&detected, &id, std::ref(soldiers), dim_x, dim_y);
    
    if (detected) {
        double next_x, next_y;
        int8_t direction;
        CalculateNextPos_by_victim(&next_x, &next_y, &direction, id, soldiers, time.count());

        std::shared_ptr<Soldier> &victim = soldiers.at(id);
        RadialHitbox hit_zone(position.getXPos(), position.getYPos(), hit_scope);
        if (hit_zone.hits(victim->getPosition())) {
            move(OFF, direction);
            attack(ON, victim);
            return;
        }
        Position next_pos(next_x, next_y, width, height, dim_x, dim_y);
        attack(OFF, nullptr);
        move(ON, direction);
        for (auto i = zombies.begin(); i != zombies.end(); i++) {
            Position other_pos = i->second->getPosition();
            if (i->second->getId() == zombie_id) continue;
            if (i->second->isDying() || i->second->isDead()) continue;
            if (next_pos.collides(other_pos)) {
                return;
            }
        }
        position = next_pos;
        return;
    }

    detect_screaming_witch(&detected, &id, std::ref(zombies), dim_x, dim_y);

    if (detected) {
        double next_x, next_y;
        int8_t direction;
        CalculateNextPos_by_witch(&next_x, &next_y, &direction, id, zombies, time.count());

        std::shared_ptr<Zombie> &witch = zombies.at(id);
        RadialHitbox hit_zone(position.getXPos(), position.getYPos(), hit_scope);
        if (hit_zone.hits(witch->getPosition())) {
            move(OFF, direction);
            idle(ON);
            return;
        }
        Position next_pos(next_x, next_y, width, height, dim_x, dim_y);
        move(ON, direction);

        for (auto i = zombies.begin(); i != zombies.end(); i++) {
            Position other_pos = i->second->getPosition();
            if (i->second->getId() == zombie_id) continue;
            if (next_pos.collides(other_pos)) {
                move(OFF, direction);
                return;
            }
        }
        position = next_pos;
        return;
    }

    move(OFF, dir_x);
    attack(OFF, nullptr);
}

void Zombie::simulateAttack(void) {
    att_vic->recvDamage(ON, damage);
}

/* GETTERS */

bool Zombie::isDead(void) {
    return (!alive);
}

bool Zombie::isDying(void) {
    return (dying);
}

double Zombie::getWidth(void) {
    return width;
}
double Zombie::getHeight(void) {
    return height;
}

uint32_t Zombie::getId(void) {
    return zombie_id;
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

double Zombie::getActualHealth(void) {
    return actual_health;
}

Position& Zombie::getPosition(void) {
    return std::ref(position);
}

const Position& Zombie::seePosition(void) const {
    return std::ref(position);
}

bool Distance_from_left_is_minor::operator()(std::shared_ptr<Zombie> below, std::shared_ptr<Zombie> above) {
        if (below->seePosition().getXPos() > above->seePosition().getXPos()) {
            return true;
        }
 
        return false;
}

bool Distance_from_right_is_minor::operator()(std::shared_ptr<Zombie> below, std::shared_ptr<Zombie> above) {
        if (below->seePosition().getXPos() < above->seePosition().getXPos()) {
            return true;
        }
 
        return false;
}

/* SETTERS */

void Zombie::setPosition(Position&& new_pos) {
    position = new_pos;
}

uint8_t Zombie::isDeadFeedback(void) {
    if (!alive) return DEAD;
    return ALIVE;
}

void Zombie::setRandomPosition(
        const std::map<uint32_t, std::shared_ptr<Soldier>> &soldiers,
        const std::map<uint32_t, std::shared_ptr<Zombie>> &zombies, double dim_x, double dim_y) {
    using std::random_device;
    using std::mt19937;
    using std::uniform_int_distribution;
    using std::uint32_t;
    //std::cout << dim_x << "-> centro de masa zombie \n";

    random_device rd;
    mt19937 mt(rd());
    //uniform_int_distribution<int32_t> distx(dim_x * 0.45, dim_x * 0.45 + SPAWNRANGE);
    uniform_int_distribution<int32_t> distx(dim_x - 1000, dim_x + 1000);
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
