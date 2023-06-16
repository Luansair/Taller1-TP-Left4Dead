#include "../../../include/GameLogic/Zombies/zombiefactory.h"

std::shared_ptr<Zombie> ZombieFactory::create(uint32_t zombie_id, uint8_t zombie_type) {

    switch(zombie_type) {
        case INFECTED: {
            return std::shared_ptr<Zombie> (new Infected(zombie_id, RIGHT, 2, 6, 1, 100));
        }
    }
    return {nullptr};
}
