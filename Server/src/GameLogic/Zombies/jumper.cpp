#include "../../../include/GameLogic/Zombies/jumper.h"
#include <random>

/* CONSTRUCTOR */

Jumper::Jumper(
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
    Zombie(zombie_id, width, height, speed, health, sight, listening_range, hit_scope, damage, die_cooldown, stunned_cooldown) {
}

// void Jumper::jump_attack(uint8_t state) {
//     switch(state) {
//         case ON:
//             jump_attacking = true;
//             moving = attacking = being_hurt = waiting_to_jump = false;
//             break;
//         case OFF:
//             jump_attacking = false;
//             att_vic = nullptr;
//             break;
//     }
// }

// void Jumper::start_wait(uint8_t state, std::shared_ptr<Soldier> victim) {
//     switch(state) {
//         case ON:
//             waiting_to_jump = true;
//             att_vic = victim;
//             moving = attacking = being_hurt = jump_attacking = false;
//             break;
//         case OFF:
//             waiting_to_jump = false;
//             att_vic = nullptr;
//             break;
//     }
// }

// void Jumper::keep_waiting_to_jump(uint8_t state) {
//     switch(state) {
//         case ON:
//             attacking = moving = being_hurt = jump_attacking = false;
//             break;
//         case OFF:
//             break;
//     }
// }

// void Jumper::keep_jumping(uint8_t state) {
//     switch(state) {
//         case ON:
//             attacking = moving = being_hurt = waiting_to_jump = false;
//             break;
//         case OFF:
//             break;
//     }
// }

// void Jumper::simulate(std::chrono::_V2::system_clock::time_point real_time,
//     std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
//     std::map<uint32_t, std::shared_ptr<Zombie>>& zombies, double dim_x, double dim_y) {
//     if (dying) simulateDie(real_time);
//     if (being_hurt) simulateRecvDamage(real_time, soldiers);
//     if (waiting_to_jump) simulateWaitToJump(real_time);
//     if (jump_attacking) simulateJumpAttack(real_time, soldiers, zombies, dim_x, dim_y);
//     if (attacking) simulateAttack(real_time, soldiers, zombies, dim_x);
//     if (!dying && !waiting_to_jump && !jump_attacking) simulateMove(real_time, soldiers, zombies, dim_x, dim_y);
//     last_step_time = real_time;
// }

// void Jumper::simulateWaitToJump(std::chrono::_V2::system_clock::time_point real_time) {
//     std::chrono::duration<double> time = real_time - start_wait_time;
//     if (time.count() > jump_wait) {
//         jump_attack(ON);
//     }
//     keep_waiting_to_jump(ON);
// }

// void Jumper::simulateJumpAttack(std::chrono::_V2::system_clock::time_point real_time,
//     std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
//     std::map<uint32_t, std::shared_ptr<Zombie>>& zombies, double dim_x, double dim_y) {

//         std::chrono::duration<double> time = real_time - last_step_time;
//         double x = getPosition().getXPos();
//         double y = getPosition().getYPos();
//         double norma = std::sqrt(std::pow(std::abs(x_jump_target - x), 2) + std::pow(std::abs(y_jump_target - y), 2));
//         double next_x = ((x_jump_target - x) / norma) * time.count() * jump_speed + x;
//         double next_y = ((y_jump_target - y) / norma) * time.count() * jump_speed + y;
//         int8_t direction;
//         if (x_jump_target - x < 0) {
//             direction = LEFT;
//         } else {
//             direction = RIGHT;
//         }

//         Position target(next_x, next_y, width, height, dim_x, dim_x);
//         position = target;
//         move(OFF, direction);
//         jump_attack(OFF);
//         if (position.collides(att_vic->getPosition())) attack(ON, att_vic);
        

// }


uint8_t Jumper::getZombieType(void) {
    return JUMPER;
}

uint8_t Jumper::getAction(void) {
    if (dying) return JUMPER_DEAD;
    if (being_hurt) return JUMPER_HURT;
    if (moving && stunned) return JUMPER_WALK;
    if (moving) return JUMPER_RUN;
    if (attacking) return JUMPER_ATTACK_1;
    // if (jump_attacking) return JUMPER_JUMP;
    // if (waiting_to_jump) return JUMPER_EATING;
    return JUMPER_IDLE;
}