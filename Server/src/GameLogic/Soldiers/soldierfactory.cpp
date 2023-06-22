#include "../../../include/GameLogic/Soldiers/soldierfactory.h"
#include "yaml-cpp/yaml.h"

std::shared_ptr<Soldier> SoldierFactory::create(uint32_t soldier_id, uint8_t soldier_type) {
    using YAML::LoadFile;
    using YAML::Node;

    WeaponFactory wpfactory;
    GrenadeFactory gfactory;
    double width, height, speed, health;
    uint8_t grenade_type;

    Node config;
    switch(soldier_type) {

        case SOLDIER_P90: {
            config = LoadFile(SERVER_CONFIG_PATH "/config.yaml")["p90soldier"];
            load_values(std::ref(config), &width, &height, &speed, &health, &grenade_type);
            return std::shared_ptr<Soldier> (new P90Soldier(soldier_id, width, height, speed, health, wpfactory.create(soldier_id, SOLDIER_P90), gfactory.create(grenade_type)));
        }
        case SOLDIER_SCOUT: {
            config = LoadFile(SERVER_CONFIG_PATH "/config.yaml")["scoutsoldier"];
            load_values(std::ref(config), &width, &height, &speed, &health, &grenade_type);
            return std::shared_ptr<Soldier> (new ScoutSoldier(soldier_id, width, height, speed, health, wpfactory.create(soldier_id, SOLDIER_SCOUT), gfactory.create(grenade_type)));
        }
        case SOLDIER_IDF: {
            config = LoadFile(SERVER_CONFIG_PATH "/config.yaml")["idfsoldier"];
            load_values(std::ref(config), &width, &height, &speed, &health, &grenade_type);
            return std::shared_ptr<Soldier> (new IdfSoldier(soldier_id, width, height, speed, health, wpfactory.create(soldier_id, SOLDIER_IDF), gfactory.create(grenade_type)));
        }
    }
    return {nullptr};
}

void SoldierFactory::load_values(const YAML::Node &node, double *width, double *height, double *speed, double *health, uint8_t *grenade) {
    *width = node["width"].as<double>();
    *height = node["height"].as<double>();
    *speed = node["speed"].as<double>();
    *health = node["health"].as<double>();
    *grenade = node["grenade_type"].as<std::uint8_t>();
}

