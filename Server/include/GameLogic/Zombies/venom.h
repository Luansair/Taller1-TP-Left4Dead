#ifndef VENOM_H_
#define VENOM_H_

#include "zombie.h"

/* Con una apariencia totalmente humana, Venom lanza un líquido/gas corrosivo. Puede lanzarlo como un
spray desde corta distancia (como se muestra en la figura) así como también puede lanzar bolas de este
líquido desde largas distancias.
El spray daña a todo jugador que esté en contacto con él */

class Venom : public Zombie {

public:

    double throw_cooldown;
    double throw_duration;
    bool throwing = false;
    std::chrono::_V2::system_clock::time_point throw_time = std::chrono::system_clock::now();
    std::chrono::_V2::system_clock::time_point last_throw_time = std::chrono::system_clock::now();

    explicit Venom(
    uint32_t zombie_id,
    double width,
    double height,
    double speed,
    double health,
    double sight,
    double listening_range,
    double hit_scope,
    double damage,
    double die_cooldown,
    double stunned_cooldown,
    double throw_cooldown,
    double throw_duration);

    void start_throw(uint8_t state);
    virtual void be_stunned(uint8_t state) override;

    void simulateMove(std::chrono::_V2::system_clock::time_point real_time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies, 
    std::map<uint32_t, std::shared_ptr<Throwable>>& throwables, double dim_x, double dim_y, ThrowableFactory& factory) override;

    void simulateThrow(std::chrono::_V2::system_clock::time_point real_time, double dim_x, double dim_y,
    std::map<uint32_t, std::shared_ptr<Throwable>>& throwables, ThrowableFactory& factory);

    uint8_t getZombieType(void) override;
    uint8_t getAction(void) override;
};

#endif  // VENOM_H_

