#include "../../../include/GameLogic/Weapons/weaponfactory.h"
#include "yaml-cpp/yaml.h"

std::unique_ptr<Weapon> WeaponFactory::create(uint32_t soldier_id, uint8_t weapon_type) {
    using YAML::LoadFile;
    using YAML::Node;

    Node node;
    std::uint16_t ammo;
    double damage, scope, reduction, bullet_speed;

    switch(weapon_type) {

        case SOLDIER_P90: {
            node = LoadFile(SERVER_CONFIG_PATH "/weapon.yaml")["p90weapon"];
            load_values(std::ref(node), &ammo, &damage, &scope, &reduction, &bullet_speed);
            return std::unique_ptr<Weapon> (new P90Weapon(soldier_id, ammo, damage, scope, reduction, bullet_speed));
        }
        case SOLDIER_SCOUT: {
            node = LoadFile(SERVER_CONFIG_PATH "/weapon.yaml")["scoutweapon"];
            load_values(std::ref(node), &ammo, &damage, &scope, &reduction, &bullet_speed);
            return std::unique_ptr<Weapon> (new ScoutWeapon(soldier_id, ammo, damage, scope, reduction, bullet_speed));
        }
        case SOLDIER_IDF: {
            node = LoadFile(SERVER_CONFIG_PATH "/weapon.yaml")["idfweapon"];
            load_values(std::ref(node), &ammo, &damage, &scope, &reduction, &bullet_speed);
            return std::unique_ptr<Weapon> (new IdfWeapon(soldier_id, ammo, damage, scope, reduction, bullet_speed));
        }
    }
    return {nullptr};
}

void WeaponFactory::load_values(const YAML::Node &node, uint16_t *ammo, double *damage,
double *scope, double *reduction, double *bullet_speed) {
    *ammo = node["ammo"].as<std::uint16_t>();
    *damage = node["damage"].as<double>();
    *scope = node["scope"].as<double>();
    *reduction = node["damage_reduction_coef"].as<double>();
    *bullet_speed = node["bullet_speed"].as<double>();
}
