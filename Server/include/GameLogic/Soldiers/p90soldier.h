#ifndef P90SOLDIER_H_
#define P90SOLDIER_H_

#include "soldier.h"

class P90Soldier : public Soldier {

public:
    explicit P90Soldier(
    uint32_t soldier_id,
    double width,
    double height,
    double speed,
    double health,
    std::unique_ptr<Weapon>&& weapon);

    virtual uint8_t getSoldierType(void) override;
    
    virtual uint8_t getAction(void) override;

    virtual ~P90Soldier() override = default;
};

#endif  // P90SOLDIER_H_
