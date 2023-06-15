#include "../../../include/GameLogic/Weapons/weaponfactory.h"
#include "yaml-cpp/yaml.h"

std::unique_ptr<Weapon> WeaponFactory::create(uint8_t weapon_type) {
    using YAML::LoadFile;
    using YAML::Node;

    Node p90w_config = LoadFile(SERVER_CONFIG_PATH "/config.yaml")["p90weapon"];

    const auto p90w_ammo =
        p90w_config["ammo"].as<std::uint8_t>();
    const auto p90w_damage =
        p90w_config["damage"].as<std::uint8_t>();
    const auto p90w_scope =
        p90w_config["scope"].as<std::uint8_t>();
    const auto p90w_reduction =
        p90w_config["damage_reduction_coef"].as<float>();

    Node scoutw_config = LoadFile(SERVER_CONFIG_PATH "/config.yaml")["scoutweapon"];

    const auto scoutw_ammo =
        scoutw_config["ammo"].as<std::uint8_t>();
    const auto scoutw_damage =
        scoutw_config["damage"].as<std::uint8_t>();
    const auto scoutw_scope =
        scoutw_config["scope"].as<std::uint8_t>();
    const auto scoutw_reduction =
        scoutw_config["damage_reduction_coef"].as<float>();   

    Node idfw_config = LoadFile(SERVER_CONFIG_PATH "/config.yaml")["idfweapon"];

    const auto idfw_ammo =
        idfw_config["ammo"].as<std::uint8_t>();
    const auto idfw_damage =
        idfw_config["damage"].as<std::uint8_t>();
    const auto idfw_scope =
        idfw_config["scope"].as<std::uint8_t>();
    const auto idfw_reduction =
        idfw_config["damage_reduction_coef"].as<float>();

    switch(weapon_type) {
        case P90WEAPON: {
            return std::unique_ptr<Weapon> (new P90Weapon(p90w_ammo, p90w_damage, p90w_scope, p90w_reduction));
        }
        case SCOUTWEAPON: {
            return std::unique_ptr<Weapon> (new ScoutWeapon(scoutw_ammo, scoutw_damage, scoutw_scope, scoutw_reduction));
        }
        case IDFWEAPON: {
            return std::unique_ptr<Weapon> (new IdfWeapon(idfw_ammo, idfw_damage, idfw_scope, idfw_reduction));
        }
    }
    return {nullptr};
}
