#include "../../../include/GameLogic/Zombies/witch.h"
#include "../../../include/GameLogic/Soldiers/soldier.h"
#include <random>

/* CONSTRUCTOR */

Witch::Witch(
    uint32_t zombie_id,
    double width,
    double height,
    double speed,
    double health) :
    Zombie(zombie_id, width, height, speed, health) {
}

void Witch::scream(uint8_t state) {
    switch(state) {
    case ON:
        screaming = true;
        moving = attacking = being_hurt = false;
        break;
    case OFF:
        screaming = false;
        break;
    }
}

void Witch::simulateScream(std::chrono::_V2::system_clock::time_point real_time) {
    if (screaming) {
        std::chrono::duration<double> time = real_time - scream_time;
        if (time.count() > scream_duration) { scream(OFF); last_scream_time = real_time; return;}
    } else {
        std::chrono::duration<double> time = real_time - last_scream_time;
        if (time.count() > scream_cooldown) { scream(ON); scream_time = real_time; return;}
    }
}

void Witch::simulateMove(std::chrono::_V2::system_clock::time_point real_time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies, 
    std::map<uint32_t, std::shared_ptr<Throwable>>& throwables, double dim_x, double dim_y) {
    std::chrono::duration<double> time = real_time - last_step_time;

    simulateScream(real_time);
    if (screaming) return;
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
        position = next_pos;
        return;
    }

    move(OFF, dir_x);
    attack(OFF, nullptr);
}

uint8_t Witch::getZombieType(void) {
    return WITCH;
}

uint8_t Witch::getAction(void) {
    if (dying) return WITCH_DEAD;
    if (being_hurt) return WITCH_HURT;
    if (moving) return WITCH_RUN;
    if (attacking) return WITCH_ATTACK_1;
    if (screaming) return WITCH_SCREAM;
    return WITCH_IDLE;
}
