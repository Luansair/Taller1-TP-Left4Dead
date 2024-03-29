#include <gtest/gtest.h>
#include "GameLogic/Soldiers/soldier.h"
#include "GameLogic/Zombies/zombie.h"
#include "GameLogic/Soldiers/soldierfactory.h"
#include "GameLogic/Weapons/weaponfactory.h"
#include "GameLogic/Throwables/throwablesfactory.h"
#include "GameLogic/Zombies/zombiefactory.h"
#include "GameLogic/Throwables/throwable.h"
#include "GameLogic/position.h"
#include "yaml-cpp/yaml.h"

using YAML::LoadFile;
using YAML::Node;
Node zombie_config = LoadFile(SERVER_CONFIG_PATH "/zombie.yaml")["infected"];

const auto zombie_width =
    zombie_config["width"].as<double>();
const auto zombie_height =
    zombie_config["height"].as<double>();
const auto zombie_speed =
    zombie_config["speed"].as<double>();
const auto zombie_health =
    zombie_config["health"].as<double>();

Node p90_config = LoadFile(SERVER_CONFIG_PATH "/soldier.yaml")["p90soldier"];

const auto p90_width =
    p90_config["width"].as<double>();
const auto p90_height =
    p90_config["height"].as<double>();
const auto p90_speed =
    p90_config["speed"].as<double>();
const auto p90_health =
    p90_config["health"].as<double>();
const auto p90_grenade =
    p90_config["t_type"].as<std::uint8_t>();

Node scout_config = LoadFile(SERVER_CONFIG_PATH "/soldier.yaml")["scoutsoldier"];

const auto scout_width =
    scout_config["width"].as<double>();
const auto scout_height =
    scout_config["height"].as<double>();
const auto scout_speed =
    scout_config["speed"].as<double>();
const auto scout_health =
    scout_config["health"].as<double>();
const auto scout_grenade =
    scout_config["t_type"].as<std::uint8_t>();

Node idf_config = LoadFile(SERVER_CONFIG_PATH "/soldier.yaml")["idfsoldier"];

const auto idf_width =
    idf_config["width"].as<double>();
const auto idf_height =
    idf_config["height"].as<double>();
const auto idf_speed =
    idf_config["speed"].as<double>();
const auto idf_health =
    idf_config["health"].as<double>();
const auto idf_grenade =
    idf_config["t_type"].as<std::uint8_t>();

Node p90w_config = LoadFile(SERVER_CONFIG_PATH "/weapon.yaml")["p90weapon"];

const auto p90w_ammo =
    p90w_config["ammo"].as<std::uint16_t>();
const auto p90w_damage =
    p90w_config["damage"].as<double>();
const auto p90w_scope =
    p90w_config["scope"].as<double>();
const auto p90w_reduction =
    p90w_config["damage_reduction_coef"].as<double>();
const auto p90w_speed=
    p90w_config["bullet_speed"].as<double>();

Node scoutw_config = LoadFile(SERVER_CONFIG_PATH "/weapon.yaml")["scoutweapon"];

const auto scoutw_ammo =
    scoutw_config["ammo"].as<std::uint16_t>();
const auto scoutw_damage =
    scoutw_config["damage"].as<double>();
const auto scoutw_scope =
    scoutw_config["scope"].as<double>();
const auto scoutw_reduction =
    scoutw_config["damage_reduction_coef"].as<double>();   

Node idfw_config = LoadFile(SERVER_CONFIG_PATH "/weapon.yaml")["idfweapon"];

const auto idfw_ammo =
    idfw_config["ammo"].as<std::uint16_t>();
const auto idfw_damage =
    idfw_config["damage"].as<double>();
const auto idfw_scope =
    idfw_config["scope"].as<double>();
const auto idfw_reduction =
    idfw_config["damage_reduction_coef"].as<double>();

TEST(weapon_test, Test00CreateWeapon) {
    WeaponFactory wfactory;

    ASSERT_NO_FATAL_FAILURE(wfactory.create(0,SOLDIER_P90));
    ASSERT_NO_FATAL_FAILURE(wfactory.create(1,SOLDIER_SCOUT));
    ASSERT_NO_FATAL_FAILURE(wfactory.create(4,SOLDIER_IDF));
}

TEST(weapon_test, Test01ShootP90) {
    ZombieFactory zfactory;
    SoldierFactory sfactory;
    uint32_t counter = 0;
    ThrowableFactory tfactory(std::ref(counter));
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::map<uint32_t, std::shared_ptr<Throwable>> throwables;
    std::shared_ptr<Soldier> soldier = sfactory.create(1, SOLDIER_P90);
    std::shared_ptr<Zombie> zombie = zfactory.create(2, ZOMBIE);
    Position pos(10, 10, soldier->getWidth(), soldier->getHeight(),100,100);
    Position pos2(95, 10, zombie->getWidth(), zombie->getHeight(),100,100);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    ASSERT_NO_THROW(zombie->setPosition(std::move(pos2)));
    zombies.emplace(2, std::move(zombie));
    soldier->shoot(ON);
    std::chrono::_V2::system_clock::time_point real_time = std::chrono::system_clock::now();
    soldier->simulate(real_time, std::ref(soldiers), std::ref(zombies), std::ref(throwables), 100,100, std::ref(tfactory), 50);
    std::shared_ptr<Zombie> &victim = zombies.at(2);
    victim->simulate(real_time, soldiers, zombies, throwables, 100, 100, std::ref(tfactory));
    ASSERT_NEAR(victim->getActualHealth(), zombie_health - p90w_damage * (1.0 - (((0.005 * p90w_speed) - 85.0) / (0.005 * p90w_speed))), 0.5);

}

TEST(weapon_test, Test02ShootP90ToTwoZombiesInTheSameRow) {
    SoldierFactory sfactory;
    uint32_t counter = 0;
    ThrowableFactory tfactory(std::ref(counter));
    ZombieFactory zfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::map<uint32_t, std::shared_ptr<Throwable>> throwables;
    std::shared_ptr<Soldier> soldier = sfactory.create(1, SOLDIER_P90);
    std::shared_ptr<Zombie> zombie = zfactory.create(2, ZOMBIE);
    std::shared_ptr<Zombie> zombie2 = zfactory.create(3, ZOMBIE);
    Position pos(10, 10, soldier->getWidth(), soldier->getHeight(),100,100);
    Position pos2(15, 10, zombie->getWidth(), zombie->getHeight(),100,100);
    Position pos3(20, 10, zombie2->getWidth(), zombie2->getHeight(),100,100);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    ASSERT_NO_THROW(zombie->setPosition(std::move(pos2)));
    ASSERT_NO_THROW(zombie2->setPosition(std::move(pos3)));
    zombies.emplace(2, std::move(zombie));
    zombies.emplace(3, std::move(zombie2));
    soldier->shoot(ON);
    std::chrono::_V2::system_clock::time_point real_time = std::chrono::system_clock::now();
    soldier->simulate(real_time, std::ref(soldiers), std::ref(zombies), std::ref(throwables), 100, 100, std::ref(tfactory), 50);
    std::shared_ptr<Zombie> &victim2 = zombies.at(2);
    std::shared_ptr<Zombie> &victim3 = zombies.at(3);
    victim2->simulate(real_time, soldiers, zombies, throwables, 100, 100, std::ref(tfactory));
    victim3->simulate(real_time, soldiers, zombies, throwables, 100, 100, std::ref(tfactory));
    ASSERT_NEAR(victim2->getActualHealth(), zombie_health - p90w_damage * (1.0 - (((0.005 * p90w_speed) - 5.0) / (0.005 * p90w_speed))), 0.5);
    ASSERT_NEAR(victim3->getActualHealth(), zombie_health, 0.5);

}

TEST(weapon_test, Test03ShootP90AndMiss) {
    SoldierFactory sfactory;
    uint32_t counter = 0;
    ThrowableFactory tfactory(std::ref(counter));
    ZombieFactory zfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::map<uint32_t, std::shared_ptr<Throwable>> throwables;
    std::shared_ptr<Soldier> soldier = sfactory.create(1, SOLDIER_P90);
    std::shared_ptr<Zombie> zombie = zfactory.create(2, ZOMBIE);
    Position pos(100, 10, soldier->getWidth(), soldier->getHeight(),100,100);
    Position pos2(500, 100, zombie->getWidth(), zombie->getHeight(),100,100);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    ASSERT_NO_THROW(zombie->setPosition(std::move(pos2)));
    zombies.emplace(2, std::move(zombie));
    soldier->shoot(ON);
    std::chrono::_V2::system_clock::time_point real_time = std::chrono::system_clock::now();
    soldier->simulate(real_time, std::ref(soldiers), std::ref(zombies), std::ref(throwables), 100, 100, std::ref(tfactory), 50);
    std::shared_ptr<Zombie> &victim = zombies.at(2);
    victim->simulate(real_time, soldiers, zombies, throwables, 100, 100, std::ref(tfactory));
    ASSERT_NEAR(victim->getActualHealth(), zombie_health, 0.5);

}

TEST(weapon_test, Test04ShootScout) {
    SoldierFactory sfactory;
    uint32_t counter = 0;
    ThrowableFactory tfactory(std::ref(counter));
    ZombieFactory zfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::map<uint32_t, std::shared_ptr<Throwable>> throwables;
    std::shared_ptr<Soldier> soldier = sfactory.create(1, SOLDIER_SCOUT);
    std::shared_ptr<Zombie> zombie = zfactory.create(2, ZOMBIE);
    Position pos(10, 10, soldier->getWidth(), soldier->getHeight(),100,100);
    Position pos2(15, 10, zombie->getWidth(), zombie->getHeight(),100,100);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    ASSERT_NO_THROW(zombie->setPosition(std::move(pos2)));
    zombies.emplace(2, std::move(zombie));
    soldier->shoot(ON);
    std::chrono::_V2::system_clock::time_point real_time = std::chrono::system_clock::now();
    soldier->simulate(real_time, std::ref(soldiers), std::ref(zombies), std::ref(throwables), 100, 100, std::ref(tfactory), 50);
    std::shared_ptr<Zombie> &victim = zombies.at(2);
    victim->simulate(real_time, soldiers, zombies, throwables, 100, 100, std::ref(tfactory));
    ASSERT_NEAR(victim->getActualHealth(), zombie_health - scoutw_damage, 0.5);

}

TEST(weapon_test, Test05ShootScoutToTwoSoldiersInTheSameRow) {
    SoldierFactory sfactory;
    uint32_t counter = 0;
    ThrowableFactory tfactory(std::ref(counter));
    ZombieFactory zfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::map<uint32_t, std::shared_ptr<Throwable>> throwables;
    std::shared_ptr<Soldier> soldier = sfactory.create(1, SOLDIER_SCOUT);
    std::shared_ptr<Zombie> zombie = zfactory.create(2, ZOMBIE);
    std::shared_ptr<Zombie> zombie2 = zfactory.create(3, ZOMBIE);
    Position pos(10, 10, soldier->getWidth(), soldier->getHeight(),100,100);
    Position pos2(15, 10, zombie->getWidth(), zombie->getHeight(),100,100);
    Position pos3(20, 10, zombie2->getWidth(), zombie2->getHeight(),100,100);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    ASSERT_NO_THROW(zombie->setPosition(std::move(pos2)));
    ASSERT_NO_THROW(zombie2->setPosition(std::move(pos3)));
    zombies.emplace(2, std::move(zombie));
    zombies.emplace(3, std::move(zombie2));
    soldier->shoot(ON);
    std::chrono::_V2::system_clock::time_point real_time = std::chrono::system_clock::now();
    soldier->simulate(real_time, std::ref(soldiers), std::ref(zombies), std::ref(throwables), 100, 100, std::ref(tfactory), 50);
    std::shared_ptr<Zombie> &victim2 = zombies.at(2);
    std::shared_ptr<Zombie> &victim3 = zombies.at(3);
    victim2->simulate(real_time, soldiers, zombies, throwables, 100, 100, std::ref(tfactory));
    victim3->simulate(real_time, soldiers, zombies, throwables, 100, 100, std::ref(tfactory));
    ASSERT_NEAR(victim2->getActualHealth(), zombie_health - scoutw_damage , 0.5);
    ASSERT_NEAR(victim3->getActualHealth(), zombie_health - scoutw_damage * scoutw_reduction , 0.5);

}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}