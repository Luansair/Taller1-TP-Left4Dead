#include "../../../include/GameLogic/Weapons/idfweapon.h"
#include "../../../include/GameLogic/Soldiers/soldier.h"
#include "../../../include/GameLogic/Zombies/zombie.h"

IdfWeapon::IdfWeapon(uint32_t soldier_id,uint16_t ammo, double damage, double scope, double reduction, double bullet_speed) :
    soldier_id(soldier_id),
    ammo(ammo),
    actual_ammo(ammo),
    damage(damage),
    scope(scope),
    damage_reduction_coef(reduction),
    bullet_speed(bullet_speed) {
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
    if (dir == RIGHT) {
        double x_coord = from.getXPos() + time * bullet_speed;
        if ((x_coord) > dim_x) x_coord = dim_x;
        hitbox.setValues(from.getXPos(), x_coord, from.getYPos() - scope * HALF, from.getYPos() + scope * HALF);
    } else if (dir == LEFT) {
        double x_coord = from.getXPos() - time * bullet_speed;
        if ((x_coord) < 0) x_coord = 0;
        hitbox.setValues(x_coord, from.getXPos(), from.getYPos() - scope * HALF, from.getYPos() + scope * HALF);
    }

    double max_distance = bullet_speed * time;
    double distance = max_distance; // distancia maxima
    double new_distance;
    uint32_t victim_id;
    bool collision = false;

    // verifico las colisiones.
    for (auto i = zombies.begin(); i != zombies.end(); i++) {
        Position victim_pos = i->second->getPosition();
        if (hitbox.shoot_hits(victim_pos) && !(i->second->dying)) {
            if (dir == RIGHT) {
                new_distance = std::abs(from.getXPos() - victim_pos.getXPos());
            } else if (dir == LEFT) {
                new_distance = std::abs(from.getXPos() - victim_pos.getXPos());
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
        double actual_damage = damage * ((max_distance - distance) / (max_distance));
        (zombies.at(victim_id))->recvDamage(ON, actual_damage, soldier_id);
    }
    // resto balas/rafagas
    actual_ammo -= 1;
    bullets_fired += 1;
    return true;
}

void IdfWeapon::reload(void) {
    actual_ammo = ammo;
}


uint16_t IdfWeapon::getAmmo(void) {
    return ammo;
}

uint16_t IdfWeapon::getActualAmmo(void) {
    return actual_ammo;
}

uint32_t IdfWeapon::getBulletsFired() {
    return bullets_fired;
}