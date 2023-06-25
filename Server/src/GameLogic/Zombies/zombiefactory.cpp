#include "../../../include/GameLogic/Zombies/zombiefactory.h"
#include "yaml-cpp/yaml.h"

std::shared_ptr<Zombie> ZombieFactory::create(uint32_t zombie_id, uint8_t zombie_type) {
    using YAML::LoadFile;
    using YAML::Node;

    Node node;
    double width, height, speed, health, sight, listening_range, hit_scope, die_cooldown, stunned_cooldown, damage;

    switch(zombie_type) {
        case ZOMBIE: {
            node = LoadFile(SERVER_CONFIG_PATH "/zombie.yaml")["infected"];
            load_values(std::ref(node), &width, &height, &speed, &health, &sight,
            &listening_range, &hit_scope, &die_cooldown, &stunned_cooldown, &damage);
            return std::shared_ptr<Zombie> (new Infected(zombie_id, width, height, speed, 
            health, sight, listening_range, hit_scope, damage, die_cooldown, stunned_cooldown));
        }
        case SPEAR: {
            node = LoadFile(SERVER_CONFIG_PATH "/zombie.yaml")["spear"];
            load_values(std::ref(node), &width, &height, &speed, &health, &sight,
            &listening_range, &hit_scope, &die_cooldown, &stunned_cooldown, &damage);
            return std::shared_ptr<Zombie> (new Spear(zombie_id, width, height, speed, 
            health, sight, listening_range, hit_scope, damage, die_cooldown, stunned_cooldown));
        }
        case JUMPER: {
            node = LoadFile(SERVER_CONFIG_PATH "/zombie.yaml")["jumper"];
            load_values(std::ref(node), &width, &height, &speed, &health, &sight,
            &listening_range, &hit_scope, &die_cooldown, &stunned_cooldown, &damage);
            return std::shared_ptr<Zombie> (new Jumper(zombie_id, width, height, speed, 
            health, sight, listening_range, hit_scope, damage, die_cooldown, stunned_cooldown));
        }
        case WITCH: {
            node = LoadFile(SERVER_CONFIG_PATH "/zombie.yaml")["witch"];
            load_values(std::ref(node), &width, &height, &speed, &health, &sight,
            &listening_range, &hit_scope, &die_cooldown, &stunned_cooldown, &damage);

            double scream_duration = node["scream_duration"].as<double>();
            double scream_cooldown = node["scream_cooldown"].as<double>();
            return std::shared_ptr<Zombie> (new Witch(zombie_id, width, height, speed, 
            health, sight, listening_range, hit_scope, damage, die_cooldown, stunned_cooldown,
            scream_duration, scream_cooldown));
        }
        case VENOM: {
            node = LoadFile(SERVER_CONFIG_PATH "/zombie.yaml")["venom"];
            load_values(std::ref(node), &width, &height, &speed, &health, &sight,
            &listening_range, &hit_scope, &die_cooldown, &stunned_cooldown, &damage);

            double throw_duration = node["throw_duration"].as<double>();
            double throw_cooldown = node["throw_cooldown"].as<double>();
            return std::shared_ptr<Zombie> (new Venom(zombie_id, width, height, speed, 
            health, sight, listening_range, hit_scope, damage, die_cooldown, stunned_cooldown,
            throw_cooldown, throw_duration));
        }
    }
    return {nullptr};
}

void ZombieFactory::load_values(const YAML::Node &node, double *width, double *height,
    double *speed, double *health, double *sight, double* listening_range,
    double* hit_scope, double *die_cooldown, double *stunned_cooldown, double *damage) {
    *speed = node["speed"].as<double>();
    *damage = node["damage"].as<double>();
    *width = node["width"].as<double>();
    *health = node["health"].as<double>();
    *sight = node["sight"].as<double>();
    *listening_range = node["listening_range"].as<double>();
    *hit_scope = node["hit_scope"].as<double>();
    *die_cooldown = node["die_cooldown"].as<double>();
    *stunned_cooldown = node["stunned_cooldown"].as<double>();
}
