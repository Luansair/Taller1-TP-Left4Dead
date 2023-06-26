#ifndef THROWABLE_H_
#define THROWABLE_H_

#include "../../../../Common/include/Information/information_code.h"
#include "../../../include/GameLogic/position.h"
#include "../../../include/GameLogic/Soldiers/soldier.h"
#include "../../../include/GameLogic/Zombies/zombie.h"

#include <cstdint>
#include <utility>
#include <chrono>

class Throwable{
public:
    uint32_t throwable_id;
    double speed, scope, duration;
    int8_t dir;
    Position position;
    uint32_t thrower_id;
    bool active = false;

    std::chrono::_V2::system_clock::time_point last_step_time = std::chrono::system_clock::now();
    std::chrono::_V2::system_clock::time_point activation_time = std::chrono::system_clock::now();

    explicit Throwable(uint32_t throwable_id,
    double x, double y, double speed, double scope, double duration, 
    int8_t dir, double dim_x, double dim_y, uint32_t thrower_id);
    virtual ~Throwable() {}

    virtual void activate(uint8_t state);
    virtual void simulateThrow(std::chrono::_V2::system_clock::time_point real_time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies,  double dim_x, double dim_y);
    virtual uint8_t getThrowerType(void) = 0;
    virtual uint8_t getAction(void) = 0;
    int8_t getDirX(void);
    Position& getPosition(void);
    uint32_t getId(void);
    bool isInactive(void);
    uint8_t isInactivefeedback(void);
};

#endif  // THROWABLE_H_
