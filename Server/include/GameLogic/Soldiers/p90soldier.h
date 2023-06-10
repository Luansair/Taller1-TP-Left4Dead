#ifndef P90SOLDIER_H_
#define P90SOLDIER_H_

#include "soldier.h"

class P90Soldier : public Soldier {

public:
    explicit P90Soldier(
    uint32_t soldier_id,
    int8_t dir,
    int8_t width,
    int8_t height,
    int8_t speed,
    int16_t health,
    std::unique_ptr<Weapon>&& weapon,
    std::unique_ptr<Grenade>&& grenade);

    virtual uint8_t getSoldierType(void) override;
    
};

#endif  // P90SOLDIER_H_
