#include "../../../include/GameLogic/Soldiers/soldierfactory.h"
#include "yaml-cpp/yaml.h"

std::shared_ptr<Soldier> SoldierFactory::create(uint32_t soldier_id, uint8_t soldier_type) {
    using YAML::LoadFile;
    using YAML::Node;

    WeaponFactory wpfactory;
    double width, height, speed, health, revive_radius, revive_cooldown, reload_cooldown, throw_cooldown, throw_duration;
    uint8_t grenade_type;

    Node config;
    switch(soldier_type) {

        case SOLDIER_P90: {
            config = LoadFile(SERVER_CONFIG_PATH "/soldier.yaml")["p90soldier"];
            load_values(std::ref(config), &width, &height, &speed, &health, &grenade_type,
            &revive_radius, &revive_cooldown, &reload_cooldown, &throw_cooldown, &throw_duration);
            return std::shared_ptr<Soldier> (new P90Soldier(soldier_id, width, height, speed, 
            health, wpfactory.create(soldier_id, SOLDIER_P90),
            grenade_type, revive_radius, revive_cooldown, reload_cooldown, throw_cooldown, throw_duration));
        }
        case SOLDIER_SCOUT: {
            config = LoadFile(SERVER_CONFIG_PATH "/soldier.yaml")["scoutsoldier"];
            load_values(std::ref(config), &width, &height, &speed, &health, &grenade_type,
            &revive_radius, &revive_cooldown, &reload_cooldown, &throw_cooldown, &throw_duration);
            return std::shared_ptr<Soldier> (new ScoutSoldier(soldier_id, width, height, speed, 
            health, wpfactory.create(soldier_id, SOLDIER_SCOUT),
            grenade_type, revive_radius, revive_cooldown, reload_cooldown, throw_cooldown, throw_duration));
        }
        case SOLDIER_IDF: {
            config = LoadFile(SERVER_CONFIG_PATH "/soldier.yaml")["idfsoldier"];
            load_values(std::ref(config), &width, &height, &speed, &health, &grenade_type,
            &revive_radius, &revive_cooldown, &reload_cooldown, &throw_cooldown, &throw_duration);
            return std::shared_ptr<Soldier> (new IdfSoldier(soldier_id, width, height, speed, 
            health, wpfactory.create(soldier_id, SOLDIER_IDF),
            grenade_type, revive_radius, revive_cooldown, reload_cooldown, throw_cooldown, throw_duration));
        }
    }
    return {nullptr};
}

void SoldierFactory::load_values(const YAML::Node &node, 
double *width, double *height, double *speed, double *health, uint8_t *grenade,
double *revive_radius, double *revive_cooldown, double* reload_cooldown, double *throw_cooldown, double *throw_duration) {
    *health = node["health"].as<double>();
    *width = node["width"].as<double>();
    *height = node["height"].as<double>();
    *speed = node["speed"].as<double>();
    *revive_radius = node["revive_radius"].as<double>();
    *grenade = node["t_type"].as<std::uint8_t>();
    *revive_cooldown = node["revive_cooldown"].as<double>();
    *reload_cooldown = node["reload_cooldown"].as<double>();
    *throw_cooldown = node["throw_cooldown"].as<double>();
    *throw_duration = node["throw_duration"].as<double>();
}

