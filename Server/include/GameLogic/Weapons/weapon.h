#ifndef WEAPON_H_
#define WEAPON_H_

#include <utility>
#include <cstdint>

class Weapon {
public:
    virtual ~Weapon() {}
    virtual void shoot(void) = 0;
    virtual void reload(void) = 0;
};

#endif  // WEAPON_H_
