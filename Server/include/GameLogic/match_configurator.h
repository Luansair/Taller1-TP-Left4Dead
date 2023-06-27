#ifndef MATCH_CONFIGURATOR_H_
#define MATCH_CONFIGURATOR_H_

#include <utility>
#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include "Zombies/zombiefactory.h"

#include "../../../Common/include/Information/information_code.h"
#define SOLDIERS_MAX 100

class Zombie;
class Soldier;

class MatchConfigurator {
public:
    uint32_t amount_infected = 0;
    uint32_t amount_venom = 0;
    uint32_t amount_witch = 0;
    uint32_t amount_jumper = 0;
    uint32_t amount_spear = 0;
    uint32_t begin = SOLDIERS_MAX + 1;
    MatchConfigurator();

    void configurate(uint8_t mode, uint8_t difficulty,
    std::map<uint32_t, std::shared_ptr<Zombie>> &zombies,
    std::map<uint32_t, std::shared_ptr<Soldier>> &soldiers,
    double dim_x, double dim_y, uint32_t *code_counter, uint16_t *zombie_counter);

    void add_zombies(int amount, std::map<uint32_t, std::shared_ptr<Zombie>> &zombies,
    std::map<uint32_t, std::shared_ptr<Soldier>> &soldiers,
    double dim_x, double dim_y, uint32_t *code_counter, uint16_t *zombie_counter);

};

#endif  // MATCH_CONFIGURATOR_H_
