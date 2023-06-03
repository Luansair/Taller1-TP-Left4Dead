#ifndef P90SOLDIER_H_
#define P90SOLDIER_H_

#include "soldier.h"

class P90Soldier : public Soldier {

public:
    explicit P90Soldier(
    uint16_t x, 
    uint16_t y,
    int8_t dir,
    uint8_t width,
    uint8_t height,
    uint8_t speed,
    uint16_t health,
    std::unique_ptr<Weapon>&& weapon,
    std::unique_ptr<Grenade>&& grenade);
    
};

#endif  // P90SOLDIER_H_
