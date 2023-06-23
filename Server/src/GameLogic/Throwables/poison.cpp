#include "../../../include/GameLogic/Throwables/poison.h"

Poison::Poison(uint32_t throwable_id, double x, double y, double speed, double scope, double duration, int8_t dir, double dim_x, double dim_y, double damage) :
    Throwable(throwable_id, x, y, speed, scope, duration, dir, dim_x, dim_y),
    damage(damage) {}


void Poison::simulateThrow(
    std::chrono::_V2::system_clock::time_point real_time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies,  double dim_x, double dim_y) {
    std::chrono::duration<double> time = real_time - last_step_time;
    if (active) {
        std::chrono::duration<double> active_time = real_time - activation_time;
        if (active_time.count() >= duration) { 
            activate(OFF);  
            return; 
        }
    }
    if (!active) {activation_time = real_time; activate(ON);}
    double x_coord;
    if (dir == RIGHT) {
        x_coord = position.getXPos() + time.count() * speed;
        if (x_coord >= dim_x) { activate(OFF); return; }
    } else if (dir == LEFT) {
        x_coord = position.getXPos() - time.count() * speed;
        if (x_coord <= 0) { activate(OFF); return; }
    }
    Position next_pos(x_coord, position.getYPos(), scope, scope, dim_x, dim_y);

    for (auto i = soldiers.begin(); i != soldiers.end(); i++) {
        Position other_pos = i->second->getPosition();
        if (next_pos.collides(other_pos)) {
            i->second->recvDamage(ON, damage);
        }
    }
    position = next_pos;
    last_step_time = real_time;
}

uint8_t Poison::getThrowerType() {
    return VENOM;
}

uint8_t Poison::getAction() {
    return VENOM_ATTACK_1A;
}
