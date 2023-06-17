#include <gtest/gtest.h>
#include "GameLogic/Soldiers/soldier.h"
#include "GameLogic/Zombies/zombie.h"
#include "GameLogic/Soldiers/soldierfactory.h"
#include "GameLogic/Weapons/weaponfactory.h"
#include "GameLogic/position.h"
#include "yaml-cpp/yaml.h"

using YAML::LoadFile;
using YAML::Node;
Node p90_config = LoadFile(SERVER_CONFIG_PATH "/config.yaml")["p90soldier"];

const auto p90_width =
    p90_config["width"].as<double>();
const auto p90_height =
    p90_config["height"].as<double>();
const auto p90_speed =
    p90_config["speed"].as<double>();
const auto p90_health =
    p90_config["health"].as<double>();
const auto p90_grenade =
    p90_config["grenade_type"].as<std::uint8_t>();

Node scout_config = LoadFile(SERVER_CONFIG_PATH "/config.yaml")["scoutsoldier"];

const auto scout_width =
    scout_config["width"].as<double>();
const auto scout_height =
    scout_config["height"].as<double>();
const auto scout_speed =
    scout_config["speed"].as<double>();
const auto scout_health =
    scout_config["health"].as<double>();
const auto scout_grenade =
    scout_config["grenade_type"].as<std::uint8_t>();

Node idf_config = LoadFile(SERVER_CONFIG_PATH "/config.yaml")["idfsoldier"];

const auto idf_width =
    idf_config["width"].as<double>();
const auto idf_height =
    idf_config["height"].as<double>();
const auto idf_speed =
    idf_config["speed"].as<double>();
const auto idf_health =
    idf_config["health"].as<double>();
const auto idf_grenade =
    idf_config["grenade_type"].as<std::uint8_t>();

Node p90w_config = LoadFile(SERVER_CONFIG_PATH "/config.yaml")["p90weapon"];

const auto p90w_ammo =
    p90w_config["ammo"].as<std::uint8_t>();
const auto p90w_damage =
    p90w_config["damage"].as<double>();
const auto p90w_scope =
    p90w_config["scope"].as<double>();
const auto p90w_reduction =
    p90w_config["damage_reduction_coef"].as<double>();

Node scoutw_config = LoadFile(SERVER_CONFIG_PATH "/config.yaml")["scoutweapon"];

const auto scoutw_ammo =
    scoutw_config["ammo"].as<std::uint8_t>();
const auto scoutw_damage =
    scoutw_config["damage"].as<double>();
const auto scoutw_scope =
    scoutw_config["scope"].as<double>();
const auto scoutw_reduction =
    scoutw_config["damage_reduction_coef"].as<double>();   

Node idfw_config = LoadFile(SERVER_CONFIG_PATH "/config.yaml")["idfweapon"];

const auto idfw_ammo =
    idfw_config["ammo"].as<std::uint8_t>();
const auto idfw_damage =
    idfw_config["damage"].as<double>();
const auto idfw_scope =
    idfw_config["scope"].as<double>();
const auto idfw_reduction =
    idfw_config["damage_reduction_coef"].as<double>();

TEST(weapon_test, Test00CreateWeapon) {
    WeaponFactory wfactory;
    ASSERT_NO_FATAL_FAILURE(wfactory.create(SOLDIER_2));
    ASSERT_NO_FATAL_FAILURE(wfactory.create(SOLDIER_3));
    ASSERT_NO_FATAL_FAILURE(wfactory.create(SOLDIER_1));
}

TEST(weapon_test, Test01ShootP90) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1, SOLDIER_2);
    std::shared_ptr<Soldier> soldier2 = sfactory.create(2, SOLDIER_2);
    Position pos(10, 10, soldier->getWidth(), soldier->getHeight(),100,100);
    Position pos2(95, 10, soldier2->getWidth(), soldier2->getHeight(),100,100);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    ASSERT_NO_THROW(soldier2->setPosition(std::move(pos2)));
    soldiers.emplace(2, std::move(soldier2));
    soldier->shoot(ON);
    uint16_t time = 1000;
    soldier->simulateShoot(time, std::ref(soldiers), std::ref(zombies), 100);
    std::shared_ptr<Soldier> &victim = soldiers.at(2);
    ASSERT_NEAR(victim->getHealth(), p90_health - p90w_damage * (1.0 - ((100.0 - 85.0) / 100.0)), 0.5);

}

TEST(weapon_test, Test02ShootP90ToTwoSoldiersInTheSameRow) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1, SOLDIER_2);
    std::shared_ptr<Soldier> soldier2 = sfactory.create(2, SOLDIER_2);
    std::shared_ptr<Soldier> soldier3 = sfactory.create(3, SOLDIER_2);
    Position pos(10, 10, soldier->getWidth(), soldier->getHeight(),100,100);
    Position pos2(15, 10, soldier2->getWidth(), soldier2->getHeight(),100,100);
    Position pos3(20, 10, soldier3->getWidth(), soldier3->getHeight(),100,100);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    ASSERT_NO_THROW(soldier2->setPosition(std::move(pos2)));
    ASSERT_NO_THROW(soldier3->setPosition(std::move(pos3)));
    soldiers.emplace(2, std::move(soldier2));
    soldiers.emplace(3, std::move(soldier3));
    soldier->shoot(ON);
    uint16_t time = 20;
    soldier->simulateShoot(time, std::ref(soldiers), std::ref(zombies), 100);
    std::shared_ptr<Soldier> &victim2 = soldiers.at(2);
    std::shared_ptr<Soldier> &victim3 = soldiers.at(3);
    ASSERT_NEAR(victim2->getHealth(), p90_health - p90w_damage * (1.0 - ((100.0 - 5.0) / 100.0)), 0.5);
    ASSERT_NEAR(victim3->getHealth(), p90_health, 0.5);

}

TEST(weapon_test, Test03ShootP90AndMiss) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1, SOLDIER_2);
    std::shared_ptr<Soldier> soldier2 = sfactory.create(2, SOLDIER_2);
    Position pos(100, 10, soldier->getWidth(), soldier->getHeight(),100,100);
    Position pos2(500, 100, soldier2->getWidth(), soldier2->getHeight(),100,100);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    ASSERT_NO_THROW(soldier2->setPosition(std::move(pos2)));
    soldiers.emplace(2, std::move(soldier2));
    soldier->shoot(ON);
    uint16_t time = 10;
    soldier->simulateShoot(time, std::ref(soldiers), std::ref(zombies), 100);
    std::shared_ptr<Soldier> &victim = soldiers.at(2);
    ASSERT_NEAR(victim->getHealth(), p90_health, 0.5);

}

TEST(weapon_test, Test04ShootScout) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1, SOLDIER_3);
    std::shared_ptr<Soldier> soldier2 = sfactory.create(2, SOLDIER_2);
    Position pos(10, 10, soldier->getWidth(), soldier->getHeight(),100,100);
    Position pos2(15, 10, soldier2->getWidth(), soldier2->getHeight(),100,100);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    ASSERT_NO_THROW(soldier2->setPosition(std::move(pos2)));
    soldiers.emplace(2, std::move(soldier2));
    soldier->shoot(ON);
    uint16_t time = 10;
    soldier->simulateShoot(time, std::ref(soldiers), std::ref(zombies), 100);
    std::shared_ptr<Soldier> &victim = soldiers.at(2);
    ASSERT_NEAR(victim->getHealth(), p90_health - scoutw_damage, 0.5);

}

TEST(weapon_test, Test05ShootScoutToTwoSoldiersInTheSameRowRight) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1, SOLDIER_3);
    std::shared_ptr<Soldier> soldier2 = sfactory.create(2, SOLDIER_2);
    std::shared_ptr<Soldier> soldier3 = sfactory.create(3, SOLDIER_2);
    Position pos(10, 10, soldier->getWidth(), soldier->getHeight(),100,100);
    Position pos2(15, 10, soldier2->getWidth(), soldier2->getHeight(),100,100);
    Position pos3(20, 10, soldier3->getWidth(), soldier3->getHeight(),100,100);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    ASSERT_NO_THROW(soldier2->setPosition(std::move(pos2)));
    ASSERT_NO_THROW(soldier3->setPosition(std::move(pos3)));
    soldiers.emplace(2, std::move(soldier2));
    soldiers.emplace(3, std::move(soldier3));
    soldier->shoot(ON);
    uint16_t time = 30;
    soldier->simulateShoot(time, std::ref(soldiers), std::ref(zombies), 100);
    std::shared_ptr<Soldier> &victim2 = soldiers.at(2);
    std::shared_ptr<Soldier> &victim3 = soldiers.at(3);
    ASSERT_NEAR(victim2->getHealth(), p90_health - scoutw_damage , 0.5);
    ASSERT_NEAR(victim3->getHealth(), p90_health - scoutw_damage * scoutw_reduction , 0.5);

}

TEST(weapon_test, Test06ShootScoutToTwoSoldiersInTheSameRowLeft) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1, SOLDIER_3);
    std::shared_ptr<Soldier> soldier2 = sfactory.create(2, SOLDIER_2);
    std::shared_ptr<Soldier> soldier3 = sfactory.create(3, SOLDIER_2);
    Position pos(20, 10, soldier->getWidth(), soldier->getHeight(),100,100);
    Position pos2(15, 10, soldier2->getWidth(), soldier2->getHeight(),100,100);
    Position pos3(10, 10, soldier3->getWidth(), soldier3->getHeight(),100,100);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    ASSERT_NO_THROW(soldier2->setPosition(std::move(pos2)));
    ASSERT_NO_THROW(soldier3->setPosition(std::move(pos3)));
    soldiers.emplace(2, std::move(soldier2));
    soldiers.emplace(3, std::move(soldier3));
    soldier->move(ON, X, LEFT, NORMAL);
    soldier->shoot(ON);
    uint16_t time = 30;
    soldier->simulateMove(1, std::ref(soldiers), std::ref(zombies),100,100);
    soldier->simulateShoot(time, std::ref(soldiers), std::ref(zombies), 100);
    std::shared_ptr<Soldier> &victim2 = soldiers.at(2);
    std::shared_ptr<Soldier> &victim3 = soldiers.at(3);
    ASSERT_NEAR(victim2->getHealth(), p90_health - scoutw_damage , 0.5);
    ASSERT_NEAR(victim3->getHealth(), p90_health - scoutw_damage * scoutw_reduction , 0.5);

}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}