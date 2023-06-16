#ifndef ZOMBIEFACTORY_H_
#define ZOMBIEFACTORY_H_

#include "../Zombies/zombie.h"
#include "../Zombies/infected.h"
#include "../Zombies/jumper.h"
#include "../Zombies/spear.h"
#include "../Zombies/venom.h"

#define INFECTED 1
#define JUMPER 2
#define SPEAR 3
#define VENOM 4
#define WITCH 5

class ZombieFactory {
public:
    std::shared_ptr<Zombie> create(uint32_t Zombie_id, uint8_t Zombie_type);
};

#endif  // ZOMBIEFACTORY_H_
