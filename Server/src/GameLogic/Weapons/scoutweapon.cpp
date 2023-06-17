#include "../../../include/GameLogic/Weapons/scoutweapon.h"
#include "../../../include/GameLogic/Soldiers/soldier.h"
#include "../../../include/GameLogic/Zombies/zombie.h"

#include <queue>

ScoutWeapon::ScoutWeapon(uint8_t ammo, double damage, double scope, double reduction) :
    ammo(ammo),
    actual_ammo(ammo),
    damage(damage),
    scope(scope),
    damage_reduction_coef(reduction) {
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
    double next_x = from.getXPos() + (dir * time);
    if (dir == RIGHT) {
        hitbox.setValues(from.getXPos(), next_x, from.getYPos() - scope * 0.5, from.getYPos() + scope * 0.5);
        std::priority_queue<std::shared_ptr<Soldier>, std::vector<std::shared_ptr<Soldier>>, Distance_from_left_is_minor> victims_queue;

        for (auto i = soldiers.begin(); i != soldiers.end(); i++) {
            Position victim_pos = i->second->getPosition();
            if (hitbox.shoot_hits(victim_pos)) {
                victims_queue.push(i->second);
            }
        }

        // como tengo que ir atravesando victimas voy desencolando de la cola de prioridad
        // por cercanía y voy sacandole daño al disparo.

        double actual_damage = damage;
        while(!victims_queue.empty()) {
            const std::shared_ptr<Soldier> &victim = victims_queue.top();
            victim->recvDamage(actual_damage);
            victims_queue.pop();
            actual_damage = actual_damage * damage_reduction_coef;
        }

    } else if (dir == LEFT) {
        hitbox.setValues(next_x, from.getXPos(), from.getYPos() - scope * 0.5, from.getYPos() + scope * 0.5);
        std::priority_queue<std::shared_ptr<Soldier>, std::vector<std::shared_ptr<Soldier>>, Distance_from_right_is_minor> victims_queue;

        for (auto i = soldiers.begin(); i != soldiers.end(); i++) {
            Position victim_pos = i->second->getPosition();
            if (hitbox.shoot_hits(victim_pos)) {
                victims_queue.push(i->second);
            }
        }

        // como tengo que ir atravesando victimas voy desencolando de la cola de prioridad
        // por cercanía y voy sacandole daño al disparo.

        double actual_damage = damage;
        while(!victims_queue.empty()) {
            const std::shared_ptr<Soldier> &victim = victims_queue.top();
            victim->recvDamage(actual_damage);
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
