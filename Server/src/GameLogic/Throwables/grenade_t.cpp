#include "../../../include/GameLogic/Throwables/grenade_t.h"

Grenade_t::Grenade_t(uint32_t throwable_id,
    double x, double y, double speed, double scope, double duration, 
    int8_t dir, double dim_x, double dim_y, uint32_t thrower_id, double damage) :
    Throwable(throwable_id, x, y, speed, scope, duration, dir, dim_x, dim_y, thrower_id),
    damage(damage) {}


void Grenade_t::simulateThrow(
    std::chrono::_V2::system_clock::time_point real_time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies,  double dim_x, double dim_y) {
    std::chrono::duration<double> time = real_time - last_step_time;
    if (active) {
        std::chrono::duration<double> active_time = real_time - activation_time;
        if (active_time.count() >= duration) {
            activate(OFF);
            simulateExplosion(zombies);
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
    position = next_pos;
    last_step_time = real_time;
}

uint8_t Grenade_t::getThrowerType() {
    return SOLDIER_IDF;
}

uint8_t Grenade_t::getAction() {
    return SOLDIER_1_EXPLOSION;
}

void Grenade_t::simulateExplosion(std::map<uint32_t, std::shared_ptr<Zombie>>& zombies) {
    RadialHitbox explodezone(position.getXPos(), position.getYPos(), scope);
    for (auto i = zombies.begin(); i != zombies.end(); i++) {
        Position other_pos = i->second->getPosition();
        if (explodezone.hits(other_pos) && (i->second->screaming)) {
            double distance = std::sqrt(std::pow(std::abs(position.getXPos() - other_pos.getXPos()), 2) + std::pow(std::abs(position.getYPos() - other_pos.getYPos()), 2));
            i->second->recvDamage(ON, damage / distance, thrower_id);
        }
    }
}
