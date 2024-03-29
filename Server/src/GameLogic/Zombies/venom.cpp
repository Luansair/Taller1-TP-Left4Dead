#include "../../../include/GameLogic/Zombies/venom.h"
#include "../../../include/GameLogic/Throwables/throwablesfactory.h"
#include "../../../include/GameLogic/Throwables/throwable.h"
#include <random>
#define DELAY 0.0

/* CONSTRUCTOR */

Venom::Venom(
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
    double stunned_cooldown,
    double throw_cooldown,
    double throw_duration) :
    Zombie(zombie_id, width, height, speed, health, sight, listening_range, hit_scope, damage, die_cooldown, stunned_cooldown),
    throw_cooldown(throw_cooldown),
    throw_duration(throw_duration) {
}

void Venom::start_throw(uint8_t state) {
    switch(state) {
    case ON:
        throwing = true;
        moving = attacking = being_hurt = false;
        break;
    case OFF:
        throwing = false;
        break;
    }
}

void Venom::be_stunned(uint8_t state) {
    switch(state) {
        case ON:
            is_stunned = true;
            attacking = moving = being_hurt = screaming = throwing = false;
            break;
        case OFF:
            is_stunned = false;
            break;
    }
}

void Venom::simulateThrow(std::chrono::_V2::system_clock::time_point real_time, double dim_x, double dim_y,
std::map<uint32_t, std::shared_ptr<Throwable>>& throwables, ThrowableFactory& factory) {
    if (throwing) {
        std::chrono::duration<double> time = real_time - throw_time;
        if (time.count() > throw_duration + DELAY) { last_throw_time = real_time; start_throw(OFF); }
        if (time.count() > throw_duration) {
            uint32_t code_counter;
            std::shared_ptr<Throwable> poison = factory.create(&code_counter, POISON, position.getXPos() + dir_x * 10,
            position.getYPos(), dir_x, dim_x, dim_y, zombie_id);
            throwables.emplace(code_counter, std::move(poison)); 
            return;
        }
    } else {
        std::chrono::duration<double> time = real_time - last_throw_time;
        if (time.count() > throw_cooldown) { 
            start_throw(ON); 
            throw_time = real_time; 
            return;
        }
    }
}

void Venom::simulateMove(std::chrono::_V2::system_clock::time_point real_time,
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
        if (!CalculateNextPos_by_victim(&next_x, &next_y, &direction, id, soldiers, time.count())) return;

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
        position = next_pos;
        simulateThrow(real_time, dim_x, dim_y, throwables, factory);
        if (throwing) move(OFF, direction);
        return;
    }

    detect_screaming_witch(&detected, &id, std::ref(zombies), dim_x, dim_y);

    if (detected) {
        double next_x, next_y;
        int8_t direction;
        if(!CalculateNextPos_by_witch(&next_x, &next_y, &direction, id, zombies, time.count())) return;

        std::shared_ptr<Zombie> &witch = zombies.at(id);
        RadialHitbox hit_zone(position.getXPos(), position.getYPos(), hit_scope);
        if (hit_zone.hits(witch->getPosition())) {
            move(OFF, direction);
            return;
        }
        Position next_pos(next_x, next_y, width, height, dim_x, dim_y);
        move(ON, direction);

        // debería chequear si colisiona con otros soldados
        position = next_pos;
        return;
    }
    if (throwing) simulateThrow(real_time, dim_x, dim_y, throwables, factory);
    move(OFF, dir_x);
    attack(OFF, nullptr);
}

void Venom::simulateStunned(std::chrono::_V2::system_clock::time_point real_time) {

    if (!stunned) {
        stunned_time = real_time;
        stunned = true;
    } else {
        std::chrono::duration<double> time = real_time - stunned_time;
        if (time.count() > stunned_cooldown) {
            be_stunned(OFF);
            last_throw_time = real_time;
            throw_time = real_time;
            stunned = false;
        }
    }
}

uint8_t Venom::getZombieType(void) {
    return VENOM;
}

uint8_t Venom::getAction(void) {
    if (dying) return VENOM_DEAD;
    if (being_hurt) return VENOM_HURT;
    if (moving && stunned) return VENOM_WALK;
    if (moving) return VENOM_RUN;
    if (attacking) return VENOM_ATTACK_2;
    if (throwing) return VENOM_ATTACK_1;
    return VENOM_IDLE;
}
