#ifndef SCOUTWEAPON_H_
#define SCOUTWEAPON_H_

#define DAMAGE_REDUCTION_COEF 0.8
#define SCOUT_DAMAGE 60

#include "weapon.h"

class ScoutWeapon : public Weapon {
private:
    uint8_t ammo;
    uint8_t damage;
    uint8_t scope;
    uint8_t recoil;

public:
    explicit ScoutWeapon(uint8_t ammo, uint8_t damage, uint8_t scope, uint8_t recoil);

    void shoot(uint32_t x, uint32_t y, uint8_t dir, GameMap &map) override;

    void reload(uint8_t state) override;

};

#endif  // SCOUTWEAPON_H_
