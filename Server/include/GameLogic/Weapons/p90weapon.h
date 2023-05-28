#ifndef P90WEAPON_H_
#define P90WEAPON_H_

#include "weapon.h"

class P90Weapon : public Weapon {
private:
    uint8_t ammo;
    uint8_t damage;
    uint8_t scope;
    uint8_t recoil;

public:
    explicit P90Weapon(uint8_t ammo, uint8_t damage, uint8_t scope, uint8_t recoil);

    void shoot(void) override;

    void reload(void) override;

};

#endif  // P90WEAPON_H_
