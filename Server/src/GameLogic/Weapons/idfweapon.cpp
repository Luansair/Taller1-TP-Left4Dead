#include "../../../include/GameLogic/Weapons/idfweapon.h"
#include "../../../include/GameLogic/Soldiers/soldier.h"
#include "../../../include/GameLogic/Zombies/zombie.h"

IdfWeapon::IdfWeapon(uint8_t ammo, double damage, double scope, double reduction) :
    ammo(ammo),
    actual_ammo(ammo),
    damage(damage),
    scope(scope),
    damage_reduction_coef(reduction) {
}

bool IdfWeapon::shoot(
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
    } else if (dir == LEFT) {
        hitbox.setValues(next_x, from.getXPos(), from.getYPos() - scope * 0.5, from.getYPos() + scope * 0.5);
    }

    double distance = dim_x; // distancia maxima
    double new_distance;
    uint32_t victim_id;
    bool collision = false;

    // verifico las colisiones.
    for (auto i = soldiers.begin(); i != soldiers.end(); i++) {
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
        double actual_damage = damage * ((dim_x - distance) / dim_x);
        (soldiers.at(victim_id))->recvDamage(actual_damage);
    }
    // resto balas/rafagas
    actual_ammo -= 1;
    return true;
}

void IdfWeapon::reload(void) {
    actual_ammo = ammo;
}
