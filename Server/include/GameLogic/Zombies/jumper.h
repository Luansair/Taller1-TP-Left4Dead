#ifndef JUMPER_H_
#define JUMPER_H_

#include "zombie.h"

/* Este infectado tiene la particularidad de saltar sobre sus víctimas y producirles daño al caer sobre ellas. El
jugador puede ver que el infectado está por saltar por su característica pose en el piso. Si es lo
suficientemente rápido de reflejos, podrá correr y evitar el ataque. */

class Jumper : public Zombie {

public:
    // double jump_scope = 200.0;
    // bool jump_attacking = false;
    // bool waiting_to_jump = false;
    // double jump_speed = 500;
    // double jump_wait = 5.0;
    // double x_jump_target = 0;
    // double y_jump_target = 0;
    // std::chrono::_V2::system_clock::time_point start_wait_time = std::chrono::system_clock::now();

    explicit Jumper(
    uint32_t zombie_id,
    double width,
    double height,
    double speed,
    double health);

    // void jump_attack(uint8_t state);
    // void keep_waiting_to_jump(uint8_t state);
    // void keep_jumping(uint8_t state);
    // void start_wait(uint8_t state, std::shared_ptr<Soldier> victim);

    // void simulate(std::chrono::_V2::system_clock::time_point real_time,
    // std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    // std::map<uint32_t, std::shared_ptr<Zombie>>& zombies, double dim_x, double dim_y);
    // void simulateMove(std::chrono::_V2::system_clock::time_point real_time,
    // std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    // std::map<uint32_t, std::shared_ptr<Zombie>>& zombies, double dim_x, double dim_y) override;
    // void simulateJumpAttack(std::chrono::_V2::system_clock::time_point real_time,
    // std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    // std::map<uint32_t, std::shared_ptr<Zombie>>& zombies, double dim_x, double dim_y);
    // void simulateWaitToJump(std::chrono::_V2::system_clock::time_point real_time);

    uint8_t getZombieType(void) override;
    uint8_t getAction(void) override;
};

#endif  // JUMPER_H_
