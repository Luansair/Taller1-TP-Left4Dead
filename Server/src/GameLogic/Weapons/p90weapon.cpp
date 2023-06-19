#include "../../../include/GameLogic/Weapons/p90weapon.h"
#include "../../../include/GameLogic/Soldiers/soldier.h"
#include "../../../include/GameLogic/Zombies/zombie.h"

P90Weapon::P90Weapon(uint8_t ammo, double damage, double scope, double reduction) :
    ammo(ammo),
    actual_ammo(ammo),
    damage(damage),
    scope(scope),
    damage_reduction_coef(reduction) {
}

bool P90Weapon::shoot(
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
        hitbox.setValues(from.getXPos(), dim_x, from.getYPos() - scope * 0.5, from.getYPos() + scope * 0.5);
    } else if (dir == LEFT) {
        hitbox.setValues(0, from.getXPos(), from.getYPos() - scope * 0.5, from.getYPos() + scope * 0.5);
    }

    double distance = dim_x; // distancia maxima
    uint32_t victim_id;
    double new_distance;
    bool collision = false;

    // verifico las colisiones.
    for (auto i = zombies.begin(); i != zombies.end(); i++) {
        Position victim_pos = i->second->getPosition();
        if (hitbox.shoot_hits(victim_pos)) {
            if (dir == RIGHT) {
                new_distance = victim_pos.getXPos() - hitbox.getXMin();
            } else if (dir == LEFT) {
                new_distance = hitbox.getXMin() - victim_pos.getXPos();
            }
            if (distance > new_distance) {
                distance = new_distance;
                victim_id = i->first;
            // me tengo que quedar con el más cercano
            }
            collision = true;
        }
    }

    if (collision) {
        double actual_damage = damage * (1.0 - ((dim_x - distance) / dim_x));
        (zombies.at(victim_id))->recvDamage(actual_damage);
    }
    // resto balas/rafagas
    actual_ammo -= 1;
    return true;
}

void P90Weapon::reload(void) {
    actual_ammo = ammo;
}

