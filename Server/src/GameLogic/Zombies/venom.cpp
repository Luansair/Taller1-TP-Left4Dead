#include "../../../include/GameLogic/Zombies/venom.h"
#include "../../../include/GameLogic/Throwables/poison.h"
#include "../../../include/GameLogic/Throwables/throwable.h"
#include "../../../include/GameLogic/Throwables/grenade_t.h"
#include <random>
#define DELAY 0.0

/* CONSTRUCTOR */

Venom::Venom(
    uint32_t zombie_id,
    double width,
    double height,
    double speed,
    double health) :
    Zombie(zombie_id, width, height, speed, health) {
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

void Venom::simulateThrow(std::chrono::_V2::system_clock::time_point real_time, double dim_x, double dim_y,
std::map<uint32_t, std::shared_ptr<Throwable>>& throwables) {
    if (throwing) {
        std::chrono::duration<double> time = real_time - throw_time;
        if (time.count() > throw_duration + DELAY) { last_throw_time = real_time; start_throw(OFF); }
        if (time.count() > throw_duration) {
            std::shared_ptr<Throwable> poison(new Poison(counter++, getPosition().getXPos() + dir_x * 10,
            getPosition().getYPos() + 30, 200, 40, 1.7, dir_x, dim_x, dim_y, zombie_id, 0.1));
            throwables.emplace(counter++, std::move(poison)); 
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
    std::map<uint32_t, std::shared_ptr<Throwable>>& throwables, double dim_x, double dim_y) {
    std::chrono::duration<double> time = real_time - last_step_time;

    bool detected = false;
    uint32_t id;
    detect_screaming_witch(&detected, &id, std::ref(zombies), dim_x, dim_y);

    if (detected) {
        double next_x, next_y;
        int8_t direction;
        CalculateNextPos_by_witch(&next_x, &next_y, &direction, id, zombies, time.count());

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

    simulateThrow(real_time, dim_x, dim_y, throwables);
    if (throwing) return;
    
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
        position = next_pos;
        return;
    }

    move(OFF, dir_x);
    attack(OFF, nullptr);
}

uint8_t Venom::getZombieType(void) {
    return VENOM;
}

uint8_t Venom::getAction(void) {
    if (dying) return VENOM_DEAD;
    if (being_hurt) return VENOM_HURT;
    if (moving) return VENOM_RUN;
    if (attacking) return VENOM_ATTACK_2;
    if (throwing) return VENOM_ATTACK_1;
    return VENOM_IDLE;
}
