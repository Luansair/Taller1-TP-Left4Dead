#ifndef WITCH_H_
#define WITCH_H_

#include "zombie.h"

/* Esta infectada ocasionalmente se pone a gritar atrayendo a más infectados que llegaran corriendo a la
zona desde todas las direcciones. Los jugadores deberían eliminarla lo antes posible. */

class Witch : public Zombie {

public:
    explicit Witch(
    uint32_t zombie_id,
    double width,
    double height,
    double speed,
    double health);

    double scream_duration = 5.0;
    double scream_cooldown = 15.0;
    std::chrono::_V2::system_clock::time_point scream_time = std::chrono::system_clock::now();
    std::chrono::_V2::system_clock::time_point last_scream_time = std::chrono::system_clock::now();

    void scream(uint8_t state);

    void simulateMove(std::chrono::_V2::system_clock::time_point real_time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies, 
    std::map<uint32_t, std::shared_ptr<Throwable>>& throwables, double dim_x, double dim_y) override;
    void simulateScream(std::chrono::_V2::system_clock::time_point real_time);

    uint8_t getZombieType(void) override;
    uint8_t getAction(void) override;
};

#endif  // WITCH_H_
