#include "../../../include/GameLogic/Weapons/scoutweapon.h"
#include "../../../include/GameLogic/Soldiers/soldier.h"
#include "../../../include/GameLogic/Zombies/zombie.h"

#include <queue>

ScoutWeapon::ScoutWeapon(uint8_t ammo, uint8_t damage, uint8_t scope) :
    ammo(ammo),
    damage(damage),
    scope(scope) {
}

bool ScoutWeapon::shoot(
    Position& from,
    int8_t dir,
    uint16_t time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies) {

    if (ammo == 0) return false;
    Hitbox hitbox;

    // calculo a donde llega el disparo
    int16_t next_x = from.getXPos() + (dir * time);
    if (dir == RIGHT) {
        hitbox.setValues(from.getXPos(), next_x, from.getYPos() - scope / 2, from.getYPos() + scope / 2);
        std::priority_queue<std::shared_ptr<Soldier>, std::vector<std::shared_ptr<Soldier>>, Distance_from_left_is_minor> victims_queue;

        for (auto i = soldiers.begin(); i != soldiers.end(); i++) {
            Position victim_pos = i->second->getPosition();
            if (hitbox.shoot_hits(victim_pos)) {
                victims_queue.push(i->second);
            }
        }

        // como tengo que ir atravesando victimas voy desencolando de la cola de prioridad
        // por cercanía y voy sacandole daño al disparo.

        uint8_t actual_damage = damage;
        while(!victims_queue.empty()) {
            const std::shared_ptr<Soldier> &victim = victims_queue.top();
            victim->recvDamage(actual_damage);
            victims_queue.pop();
            actual_damage = actual_damage * DAMAGE_REDUCTION_COEF;
        }
    } else if (dir == LEFT) {
        hitbox.setValues(next_x, from.getXPos(), from.getYPos() - scope / 2, from.getYPos() + scope / 2);
        std::priority_queue<std::shared_ptr<Soldier>, std::vector<std::shared_ptr<Soldier>>, Distance_from_left_is_minor> victims_queue;

        for (auto i = soldiers.begin(); i != soldiers.end(); i++) {
            Position victim_pos = i->second->getPosition();
            if (hitbox.shoot_hits(victim_pos)) {
                victims_queue.push(i->second);
            }
        }

        // como tengo que ir atravesando victimas voy desencolando de la cola de prioridad
        // por cercanía y voy sacandole daño al disparo.

        uint8_t actual_damage = damage;
        while(!victims_queue.empty()) {
            const std::shared_ptr<Soldier> &victim = victims_queue.top();
            victim->recvDamage(actual_damage);
            victims_queue.pop();
            actual_damage = actual_damage * DAMAGE_REDUCTION_COEF;
        }
    }

    // resto balas/rafagas
    ammo -= 1;
    return true;
}

void ScoutWeapon::reload(void) {
    ammo = SCOUT_AMMO;
}
