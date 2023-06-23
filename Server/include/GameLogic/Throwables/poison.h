#ifndef POISON_H_
#define POISON_H_

#include "throwable.h"

class Poison : public Throwable {

public:
    explicit Poison() = default;

    explicit Poison(uint32_t throwable_id,
    double x, double y, double speed, double scope, double duration, 
    int8_t dir, double dim_x, double dim_y);

    virtual uint8_t getThrowerType() override;
    virtual uint8_t getAction() override;

};

#endif  // POISON_H_
