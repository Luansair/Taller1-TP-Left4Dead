#include "../../../include/GameLogic/Zombies/zombiefactory.h"

std::shared_ptr<Zombie> ZombieFactory::create(uint32_t zombie_id, uint8_t zombie_type) {

    switch(zombie_type) {
        case ZOMBIE: {
            return std::shared_ptr<Zombie> (new Infected(zombie_id, RIGHT, 2, 6, 1, 100));
        }
        case SPEAR: {
            return std::shared_ptr<Zombie> (new Spear(zombie_id, RIGHT, 2, 6, 1, 100));
        }
        case JUMPER: {
            return std::shared_ptr<Zombie> (new Jumper(zombie_id, RIGHT, 2, 6, 1, 100));
        }
        case WITCH: {
            return std::shared_ptr<Zombie> (new Witch(zombie_id, RIGHT, 2, 6, 1, 100));
        }
        case VENOM: {
            return std::shared_ptr<Zombie> (new Venom(zombie_id, RIGHT, 2, 6, 1, 100));
        }
    }
    return {nullptr};
}
