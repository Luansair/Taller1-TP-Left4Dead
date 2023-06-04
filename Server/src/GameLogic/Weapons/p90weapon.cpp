#include "../../../include/GameLogic/Weapons/p90weapon.h"
#include "../../../include/GameLogic/Soldiers/soldier.h"
#include "../../../include/GameLogic/Zombies/zombie.h"

P90Weapon::P90Weapon(uint8_t ammo, uint8_t damage, uint8_t scope) :
    ammo(ammo),
    damage(damage),
    scope(scope) {
}

bool P90Weapon::shoot(
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
    } else if (dir == LEFT) {
        hitbox.setValues(next_x, from.getXPos(), from.getYPos() - scope / 2, from.getYPos() + scope / 2);
    }

    int16_t distance = 16383; // distancia maxima
    uint32_t victim_id;
    int16_t new_distance;
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
        int8_t actual_damage = damage; // pensar forma para calcular el daño dependiendo la distancia
        (soldiers.at(victim_id))->recvDamage(actual_damage);
    }
    // resto balas/rafagas
    ammo -= 1;
    return true;
}

void P90Weapon::reload(void) {
    ammo = P90_AMMO;
}

