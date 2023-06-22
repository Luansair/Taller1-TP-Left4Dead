#include "../../../include/GameLogic/Weapons/weaponfactory.h"
#include "yaml-cpp/yaml.h"

std::unique_ptr<Weapon> WeaponFactory::create(uint32_t soldier_id, uint8_t weapon_type) {
    using YAML::LoadFile;
    using YAML::Node;

    Node node;
    std::uint16_t ammo;
    double damage, scope, reduction;

    switch(weapon_type) {

        case SOLDIER_P90: {
            node = LoadFile(SERVER_CONFIG_PATH "/config.yaml")["p90weapon"];
            load_values(std::ref(node), &ammo, &damage, &scope, &reduction);
            return std::unique_ptr<Weapon> (new P90Weapon(soldier_id, ammo, damage, scope, reduction));
        }
        case SOLDIER_SCOUT: {
            node = LoadFile(SERVER_CONFIG_PATH "/config.yaml")["scoutweapon"];
            load_values(std::ref(node), &ammo, &damage, &scope, &reduction);
            return std::unique_ptr<Weapon> (new ScoutWeapon(soldier_id, ammo, damage, scope, reduction));
        }
        case SOLDIER_IDF: {
            node = LoadFile(SERVER_CONFIG_PATH "/config.yaml")["idfweapon"];
            load_values(std::ref(node), &ammo, &damage, &scope, &reduction);
            return std::unique_ptr<Weapon> (new IdfWeapon(soldier_id, ammo, damage, scope, reduction));
        }
    }
    return {nullptr};
}

void WeaponFactory::load_values(const YAML::Node &node, uint16_t *ammo, double *damage, double *scope, double *reduction) {
    *ammo = node["ammo"].as<std::uint16_t>();
    *damage = node["damage"].as<double>();
    *scope = node["scope"].as<double>();
    *reduction = node["damage_reduction_coef"].as<double>();
}
