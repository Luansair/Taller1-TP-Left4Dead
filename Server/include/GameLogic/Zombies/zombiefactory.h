#ifndef ZOMBIEFACTORY_H_
#define ZOMBIEFACTORY_H_

#include "../Zombies/zombie.h"
#include "../Zombies/infected.h"
#include "../Zombies/jumper.h"
#include "../Zombies/spear.h"
#include "../Zombies/witch.h"
#include "../Zombies/venom.h"
#include "../../../../Common/include/Information/information_code.h"
#include "yaml-cpp/yaml.h"

class ZombieFactory {
public:
    std::shared_ptr<Zombie> create(uint32_t Zombie_id, uint8_t Zombie_type);
    void load_values(const YAML::Node &node, double *width, double *height,
    double *speed, double *health, double *sight, double* listening_range,
    double* hit_scope, double *die_cooldown, double *stunned_cooldown, double *damage);
};

#endif  // ZOMBIEFACTORY_H_
