#include "../../../include/GameLogic/Weapons/scoutweapon.h"
#include "../../../include/GameLogic/Soldiers/soldier.h"
#include "../../../include/GameLogic/Zombies/zombie.h"

#include <queue>

ScoutWeapon::ScoutWeapon(uint32_t soldier_id,uint16_t ammo, double damage, double scope, double reduction, double bullet_speed) :
    soldier_id(soldier_id),
    ammo(ammo),
    actual_ammo(ammo),
    damage(damage),
    scope(scope),
    damage_reduction_coef(reduction),
    bullet_speed(bullet_speed) {
}

bool ScoutWeapon::shoot(
    Position& from,
    int8_t dir,
    double dim_x,
    double time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies) {
    if (actual_ammo == 0) return false;
    Hitbox hitbox;

    // calculo a donde llega el disparo
    if (dir == RIGHT) {
        double x_coord = from.getXPos() + time * bullet_speed;
        if ((x_coord) > dim_x) x_coord = dim_x;
        hitbox.setValues(from.getXPos(), x_coord, from.getYPos() - scope * HALF, from.getYPos() + scope * HALF);
        std::priority_queue<std::shared_ptr<Zombie>, std::vector<std::shared_ptr<Zombie>>, Distance_from_left_is_minor> victims_queue;

        for (auto i = zombies.begin(); i != zombies.end(); i++) {
            Position victim_pos = i->second->getPosition();
            if (hitbox.shoot_hits(victim_pos) && !(i->second->dying)) {
                victims_queue.push(i->second);
            }
        }

        // como tengo que ir atravesando victimas voy desencolando de la cola de prioridad
        // por cercanía y voy sacandole daño al disparo.

        double actual_damage = damage;
        while(!victims_queue.empty()) {
            const std::shared_ptr<Zombie> &victim = victims_queue.top();
            victim->recvDamage(ON, actual_damage, soldier_id);
            victims_queue.pop();
            actual_damage = actual_damage * damage_reduction_coef;
        }

    } else if (dir == LEFT) {
        double x_coord = from.getXPos() - time * bullet_speed;
        if ((x_coord) < 0) x_coord = 0;
        hitbox.setValues(x_coord, from.getXPos(), from.getYPos() - scope * HALF, from.getYPos() + scope * HALF);
        std::priority_queue<std::shared_ptr<Zombie>, std::vector<std::shared_ptr<Zombie>>, Distance_from_right_is_minor> victims_queue;

        for (auto i = zombies.begin(); i != zombies.end(); i++) {
            Position victim_pos = i->second->getPosition();
            if (hitbox.shoot_hits(victim_pos) && !(i->second->dying)) {
                victims_queue.push(i->second);
            }
        }

        // como tengo que ir atravesando victimas voy desencolando de la cola de prioridad
        // por cercanía y voy sacandole daño al disparo.

        double actual_damage = damage;
        while(!victims_queue.empty()) {
            const std::shared_ptr<Zombie> &victim = victims_queue.top();
            victim->recvDamage(ON, actual_damage, soldier_id);
            victims_queue.pop();
            actual_damage = actual_damage * damage_reduction_coef;
        }
    }

    // resto balas/rafagas
    actual_ammo -= 1;
    return true;
}


void ScoutWeapon::reload(void) {
    actual_ammo = ammo;
}
