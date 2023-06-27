#include "../../../include/GameLogic/Throwables/smoke.h"

Smoke::Smoke(uint32_t throwable_id,
    double x, double y, double speed, double scope, double duration, 
    int8_t dir, double dim_x, double dim_y, uint32_t thrower_id, double damage) :
    Throwable(throwable_id, x, y, speed, scope, duration, dir, dim_x, dim_y, thrower_id),
    damage(damage) {}


void Smoke::simulateThrow(
    std::chrono::_V2::system_clock::time_point real_time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies,  double dim_x, double dim_y) {
    std::chrono::duration<double> time = real_time - last_step_time;
    if (active) {
        std::chrono::duration<double> active_time = real_time - activation_time;
        if (active_time.count() >= duration * 0.35 && !exploded) {
            simulateExplosion(zombies);
        }
        if (active_time.count() >= duration) {
            activate(OFF);
            return; 
        }
    }
    if (!active && !used) {activation_time = real_time; activate(ON); used = true; }
    double x_coord;

    if (exploded) {last_step_time = real_time; return;}
    if (dir == RIGHT) {
        x_coord = position.getXPos() + time.count() * speed;
        if (x_coord >= dim_x) { activate(OFF); return; }
    } else if (dir == LEFT) {
        x_coord = position.getXPos() - time.count() * speed;
        if (x_coord <= 0) { activate(OFF); return; }
    }
    Position next_pos(x_coord, position.getYPos(), scope, scope, dim_x, dim_y);
    position = next_pos;
    last_step_time = real_time;
}

uint8_t Smoke::getThrowerType() {
    return SOLDIER_SCOUT;
}

uint8_t Smoke::getAction() {
    return SOLDIER_3_SMOKE;
}

void Smoke::simulateExplosion(std::map<uint32_t, std::shared_ptr<Zombie>>& zombies) {
    RadialHitbox explodezone(position.getXPos(), position.getYPos(), scope);
    for (auto i = zombies.begin(); i != zombies.end(); i++) {
        Position other_pos = i->second->getPosition();
        if (explodezone.hits(other_pos)) {
            i->second->be_stunned(ON);
        }
    }
    exploded = true;
}
