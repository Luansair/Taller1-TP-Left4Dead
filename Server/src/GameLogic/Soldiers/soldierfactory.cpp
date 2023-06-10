#include "../../../include/GameLogic/Soldiers/soldierfactory.h"
#include "yaml-cpp/yaml.h"

std::shared_ptr<Soldier> SoldierFactory::create(uint32_t soldier_id, uint8_t soldier_type) {
    using YAML::LoadFile;
    using YAML::Node;

    WeaponFactory wpfactory;
    GrenadeFactory gfactory;

    Node p90_config = LoadFile(SERVER_CONFIG_PATH "/config.yaml")["p90soldier"];

    const auto p90_width =
        p90_config["width"].as<std::int8_t>();
    const auto p90_height =
        p90_config["height"].as<std::int8_t>();
    const auto p90_speed =
        p90_config["speed"].as<std::int8_t>();
    const auto p90_health =
        p90_config["health"].as<std::int16_t>();
    const auto p90_type =
        p90_config["type"].as<std::uint8_t>();
    const auto p90_grenade =
        p90_config["grenade_type"].as<std::uint8_t>();

    Node scout_config = LoadFile(SERVER_CONFIG_PATH "/config.yaml")["scoutsoldier"];

    const auto scout_width =
        scout_config["width"].as<std::int8_t>();
    const auto scout_height =
        scout_config["height"].as<std::int8_t>();
    const auto scout_speed =
        scout_config["speed"].as<std::int8_t>();
    const auto scout_health =
        scout_config["health"].as<std::int16_t>();
    const auto scout_type =
        scout_config["type"].as<std::uint8_t>();
    const auto scout_grenade =
        scout_config["grenade_type"].as<std::uint8_t>();

    Node idf_config = LoadFile(SERVER_CONFIG_PATH "/config.yaml")["idfsoldier"];

    const auto idf_width =
        idf_config["width"].as<std::int8_t>();
    const auto idf_height =
        idf_config["height"].as<std::int8_t>();
    const auto idf_speed =
        idf_config["speed"].as<std::int8_t>();
    const auto idf_health =
        idf_config["health"].as<std::int16_t>();
    const auto idf_type =
        idf_config["type"].as<std::uint8_t>();
    const auto idf_grenade =
        idf_config["grenade_type"].as<std::uint8_t>();

    switch(soldier_type) {
        case P90SOLDIER: {
            return std::shared_ptr<Soldier> (new P90Soldier(soldier_id, RIGHT, p90_width, p90_height, p90_speed, p90_health, std::move(wpfactory.create(p90_type)), std::move(gfactory.create(p90_grenade))));
        }
        case SCOUTSOLDIER: {
            return std::shared_ptr<Soldier> (new ScoutSoldier(soldier_id, RIGHT, scout_width, scout_height, scout_speed, scout_health, std::move(wpfactory.create(scout_type)), std::move(gfactory.create(scout_grenade))));
        }
        case IDFSOLDIER: {
            return std::shared_ptr<Soldier> (new IdfSoldier(soldier_id, RIGHT, idf_width, idf_height, idf_speed, idf_health, std::move(wpfactory.create(idf_type)), std::move(gfactory.create(idf_grenade))));
        }
    }
    return std::shared_ptr<Soldier>(nullptr);
}
