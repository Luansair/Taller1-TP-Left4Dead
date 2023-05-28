#ifndef SCOUTWEAPON_H_
#define SCOUTWEAPON_H_

#include "weapon.h"

class ScoutWeapon : public Weapon {
private:
    uint8_t ammo;
    uint8_t damage;
    uint8_t scope;
    uint8_t recoil;

public:
    explicit ScoutWeapon(uint8_t ammo, uint8_t damage, uint8_t scope, uint8_t recoil);

    void shoot(void) override;

    void reload(void) override;

};

#endif  // SCOUTWEAPON_H_
