#ifndef SCOUTWEAPON_H_
#define SCOUTWEAPON_H_

#define DAMAGE_REDUCTION_COEF 0.8
#define SCOUT_DAMAGE 60
#define SCOUT_AMMO 20

#include "weapon.h"

/* A diferencia del IDF y P90, el Scout es un rifle que dispara de a 1 bala. No obstante cada bala daña a todo
infectado que se encuentre en su trayectoria (aunque el daño de cada impacto se verá reducido conforme la
bala pasa por más infectados).
Se recarga cada 20 balas. */

class ScoutWeapon : public Weapon {
private:
    uint8_t ammo;
    uint8_t damage;

public:
    explicit ScoutWeapon(uint8_t ammo, uint8_t damage);

    void shoot(uint32_t x, uint32_t y, uint8_t dir, GameMap &map) override;

    void reload(uint8_t state) override;

};

#endif  // SCOUTWEAPON_H_
