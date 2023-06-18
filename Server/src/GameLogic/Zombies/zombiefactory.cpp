#include "../../../include/GameLogic/Zombies/zombiefactory.h"
#include "yaml-cpp/yaml.h"

std::shared_ptr<Zombie> ZombieFactory::create(uint32_t zombie_id, uint8_t zombie_type) {
    using YAML::LoadFile;
    using YAML::Node;

    Node zombie_config = LoadFile(SERVER_CONFIG_PATH "/config.yaml")["zombie"];

    const auto zombie_width =
        zombie_config["width"].as<double>();
    const auto zombie_height =
        zombie_config["height"].as<double>();
    const auto zombie_speed =
        zombie_config["speed"].as<double>();
    const auto zombie_health =
        zombie_config["health"].as<double>();

    switch(zombie_type) {
        case ZOMBIE: {
            return std::shared_ptr<Zombie> (new Infected(zombie_id, zombie_width, zombie_height, zombie_speed, zombie_health));
        }
        case SPEAR: {
            return std::shared_ptr<Zombie> (new Spear(zombie_id, zombie_width, zombie_height, zombie_speed, zombie_health));
        }
        case JUMPER: {
            return std::shared_ptr<Zombie> (new Jumper(zombie_id, zombie_width, zombie_height, zombie_speed, zombie_health));
        }
        case WITCH: {
            return std::shared_ptr<Zombie> (new Witch(zombie_id, zombie_width, zombie_height, zombie_speed, zombie_health));
        }
        case VENOM: {
            return std::shared_ptr<Zombie> (new Venom(zombie_id, zombie_width, zombie_height, zombie_speed, zombie_health));
        }
    }
    return {nullptr};
}
