#include "../../../include/GameLogic/Weapons/weaponfactory.h"
#include "yaml-cpp/yaml.h"

std::unique_ptr<Weapon> WeaponFactory::create(uint32_t soldier_id, uint8_t weapon_type) {
    using YAML::LoadFile;
    using YAML::Node;

    Node p90w_config = LoadFile(SERVER_CONFIG_PATH "/config.yaml")["p90weapon"];

    const auto p90w_ammo =
        p90w_config["ammo"].as<std::uint16_t>();
    const auto p90w_damage =
        p90w_config["damage"].as<double>();
    const auto p90w_scope =
        p90w_config["scope"].as<double>();
    const auto p90w_reduction =
        p90w_config["damage_reduction_coef"].as<double>();

    Node scoutw_config = LoadFile(SERVER_CONFIG_PATH "/config.yaml")["scoutweapon"];

    const auto scoutw_ammo =
        scoutw_config["ammo"].as<std::uint16_t>();
    const auto scoutw_damage =
        scoutw_config["damage"].as<double>();
    const auto scoutw_scope =
        scoutw_config["scope"].as<double>();
    const auto scoutw_reduction =
        scoutw_config["damage_reduction_coef"].as<double>();   

    Node idfw_config = LoadFile(SERVER_CONFIG_PATH "/config.yaml")["idfweapon"];

    const auto idfw_ammo =
        idfw_config["ammo"].as<std::uint16_t>();
    const auto idfw_damage =
        idfw_config["damage"].as<double>();
    const auto idfw_scope =
        idfw_config["scope"].as<double>();
    const auto idfw_reduction =
        idfw_config["damage_reduction_coef"].as<double>();

    switch(weapon_type) {

        case SOLDIER_P90: {
            return std::unique_ptr<Weapon> (new P90Weapon(soldier_id, p90w_ammo, p90w_damage, p90w_scope, p90w_reduction));
        }
        case SOLDIER_SCOUT: {
            return std::unique_ptr<Weapon> (new ScoutWeapon(soldier_id, scoutw_ammo, scoutw_damage, scoutw_scope, scoutw_reduction));
        }
        case SOLDIER_IDF: {
            return std::unique_ptr<Weapon> (new IdfWeapon(soldier_id, idfw_ammo, idfw_damage, idfw_scope, idfw_reduction));
        }
    }
    return {nullptr};
}
