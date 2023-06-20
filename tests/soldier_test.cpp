#include <gtest/gtest.h>
#include "GameLogic/Soldiers/soldier.h"
#include "GameLogic/Zombies/zombie.h"
#include "GameLogic/Soldiers/soldierfactory.h"
#include "GameLogic/position.h"
#include <tuple>
#include "yaml-cpp/yaml.h"

#define MAP_DIM 100.0
#define HALF 0.5

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

TEST(soldier_test, Test00CreateSoldier) {
    SoldierFactory sfactory;
    ASSERT_NO_FATAL_FAILURE(sfactory.create(1,SOLDIER_2));
    ASSERT_NO_FATAL_FAILURE(sfactory.create(2,SOLDIER_3));
    ASSERT_NO_FATAL_FAILURE(sfactory.create(3,SOLDIER_1));
}

TEST(soldier_test, Test02SetPositionToSoldier) {
    SoldierFactory sfactory;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,SOLDIER_2);
    double x0 = 10.0;
    double y0 = 10.0;
    Position pos(x0, y0, soldier->getWidth(), soldier->getHeight(), MAP_DIM, MAP_DIM);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    Position& pos1 = soldier->getPosition();
    ASSERT_EQ(pos1.getXPos(), x0);
    ASSERT_EQ(pos1.getYPos(), y0);
    std::tuple<double, double, bool> tuple {x0 - p90_width * HALF, x0 + p90_width * HALF, true};
    ASSERT_EQ(pos1.getXArea(), tuple);

}

TEST(soldier_test, Test03MoveSoldierOnXRigth) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,SOLDIER_2);
    double x0 = 10.0;
    double y0 = 10.0;
    Position pos(x0, y0, soldier->getWidth(), soldier->getHeight(), MAP_DIM, MAP_DIM);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    soldier->move(ON, X, RIGHT, NORMAL);
    double time = 1.0;
    soldier->simulateMove(time, std::chrono::steady_clock::now(), std::ref(soldiers), std::ref(zombies), MAP_DIM, MAP_DIM);
    Position& pos1 = soldier->getPosition();
    ASSERT_NEAR(pos1.getXPos(), x0 + time * p90_speed, HALF);
    ASSERT_NEAR(pos1.getYPos(), y0, HALF);
    std::tuple<double, double, bool> tuple {x0 + time * p90_speed - p90_width * HALF,
    x0 + time * p90_speed + p90_width * HALF, true};
    ASSERT_EQ(pos1.getXArea(), tuple);

}

TEST(soldier_test, Test04MoveSoldierAWhileOnXRight) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,SOLDIER_2);
    double x0 = 10.0;
    double y0 = 10.0;
    Position pos(x0, y0, soldier->getWidth(), soldier->getHeight(), MAP_DIM, MAP_DIM);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    soldier->move(ON, X, RIGHT, NORMAL);
    double time = 10.0;
    soldier->simulateMove(time, std::chrono::steady_clock::now(), std::ref(soldiers), std::ref(zombies), MAP_DIM, MAP_DIM);
    Position& pos1 = soldier->getPosition();
    ASSERT_NEAR(pos1.getXPos(), x0 + time * p90_speed, HALF);
    ASSERT_NEAR(pos1.getYPos(), y0, HALF);
    std::tuple<double, double, bool> tuple {x0 + time * p90_speed - p90_width * HALF,
    x0 + time * p90_speed + p90_width * HALF, true};
    ASSERT_EQ(pos1.getXArea(), tuple);

}

TEST(soldier_test, Test05MoveSoldierOnXLeft) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,SOLDIER_2);
    double x0 = 10.0;
    double y0 = 10.0;
    Position pos(x0, y0, soldier->getWidth(), soldier->getHeight(), MAP_DIM, MAP_DIM);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    soldier->move(ON, X, LEFT, NORMAL);
    double time = 1.0;
    soldier->simulateMove(time, std::chrono::steady_clock::now(), std::ref(soldiers), std::ref(zombies), MAP_DIM, MAP_DIM);
    Position& pos1 = soldier->getPosition();
    ASSERT_NEAR(pos1.getXPos(), x0 - time * p90_speed, HALF);
    ASSERT_NEAR(pos1.getYPos(), y0, HALF);
    std::tuple<double, double, bool> tuple {x0 - time * p90_speed - p90_width * HALF,
    x0 - time * p90_speed + p90_width * HALF, true};
    ASSERT_EQ(pos1.getXArea(), tuple);

}

TEST(soldier_test, Test06MoveSoldierAWhileOnXleft) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,SOLDIER_2);
    double x0 = 30.0;
    double y0 = 30.0;
    Position pos(x0, y0, soldier->getWidth(), soldier->getHeight(), MAP_DIM, MAP_DIM);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    soldier->move(ON, X, LEFT, NORMAL);
    double time = 15.0;
    soldier->simulateMove(time, std::chrono::steady_clock::now(), std::ref(soldiers), std::ref(zombies), MAP_DIM, MAP_DIM);
    Position& pos1 = soldier->getPosition();
    ASSERT_NEAR(pos1.getXPos(), x0 - time * p90_speed, HALF);
    ASSERT_NEAR(pos1.getYPos(), y0, HALF);
    std::tuple<double, double, bool> tuple {x0 - time * p90_speed - p90_width * HALF,
    x0 - time * p90_speed + p90_width * HALF, true};
    ASSERT_EQ(pos1.getXArea(), tuple);

}

TEST(soldier_test, Test07MoveSoldierOnYUp) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,SOLDIER_2);
    double x0 = 10.0;
    double y0 = 10.0;
    Position pos(x0, y0, soldier->getWidth(), soldier->getHeight(), MAP_DIM, MAP_DIM);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    soldier->move(ON, Y, UP, NORMAL);
    double time = 1.0;
    soldier->simulateMove(time, std::chrono::steady_clock::now(), std::ref(soldiers), std::ref(zombies), MAP_DIM, MAP_DIM);
    Position& pos1 = soldier->getPosition();
    ASSERT_NEAR(pos1.getXPos(), x0, HALF);
    ASSERT_NEAR(pos1.getYPos(), y0 + time * p90_speed, HALF);
    std::tuple<double, double, bool> tuple {y0 + time * p90_speed - p90_height * HALF,
    y0 + time * p90_speed + p90_height * HALF, true};
    ASSERT_EQ(pos1.getYArea(), tuple);

}

TEST(soldier_test, Test08MoveSoldierOnYDown) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,SOLDIER_2);
    double x0 = 10.0;
    double y0 = 10.0;
    Position pos(x0, y0, soldier->getWidth(), soldier->getHeight(), MAP_DIM, MAP_DIM);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    soldier->move(ON, Y, DOWN, NORMAL);
    double time = 1.0;
    soldier->simulateMove(time, std::chrono::steady_clock::now(), std::ref(soldiers), std::ref(zombies), MAP_DIM, MAP_DIM);
    Position& pos1 = soldier->getPosition();
    ASSERT_NEAR(pos1.getXPos(), x0, HALF);
    ASSERT_NEAR(pos1.getYPos(), y0 - time * p90_speed, HALF);
    std::tuple<double, double, bool> tuple {y0 - time * p90_speed - p90_height * HALF,
    y0 - time * p90_speed + p90_height * HALF, true};
    ASSERT_EQ(pos1.getYArea(), tuple);

}

TEST(soldier_test, Test09MoveWithCollisionOnRight) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,SOLDIER_2);
    std::shared_ptr<Soldier> soldier2 = sfactory.create(2,SOLDIER_2);
    double x0 = 10.0;
    double y0 = 10.0;
    double x0_2 = x0 + p90_width + 1;
    double y0_2 = y0;
    Position pos(x0, y0, soldier->getWidth(), soldier->getHeight(), MAP_DIM, MAP_DIM);
    Position pos2(x0_2, y0_2, soldier2->getWidth(), soldier2->getHeight(), MAP_DIM, MAP_DIM);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    ASSERT_NO_THROW(soldier2->setPosition(std::move(pos2)));
    soldiers.emplace(2, std::move(soldier2));
    soldier->move(ON, X, RIGHT, NORMAL);
    double time = 1.0;
    soldier->simulateMove(time, std::chrono::steady_clock::now(), std::ref(soldiers), std::ref(zombies), MAP_DIM, MAP_DIM);
    Position& pos1 = soldier->getPosition();
    ASSERT_EQ(pos1.getXPos(), x0);
    ASSERT_EQ(pos1.getYPos(), y0);
    std::tuple<double, double, bool> tuple {x0 - p90_width * HALF, x0 + p90_width * HALF, true};
    ASSERT_EQ(pos1.getXArea(), tuple);

}

TEST(soldier_test, Test10MoveWithCollisionOnLeft) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,SOLDIER_2);
    std::shared_ptr<Soldier> soldier2 = sfactory.create(2,SOLDIER_2);
    double x0 = 13.0;
    double y0 = 10.0;
    double x0_2 = x0 - p90_width - 1;
    double y0_2 = y0;
    Position pos(x0, y0, soldier->getWidth(), soldier->getHeight(), MAP_DIM, MAP_DIM);
    Position pos2(x0_2, y0_2, soldier2->getWidth(), soldier2->getHeight(), MAP_DIM, MAP_DIM);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    ASSERT_NO_THROW(soldier2->setPosition(std::move(pos2)));
    soldiers.emplace(2, std::move(soldier2));
    soldier->move(ON, X, LEFT, NORMAL);
    double time = 1.0;
    soldier->simulateMove(time, std::chrono::steady_clock::now(), std::ref(soldiers), std::ref(zombies), MAP_DIM, MAP_DIM);
    Position& pos1 = soldier->getPosition();
    ASSERT_EQ(pos1.getXPos(), x0);
    ASSERT_EQ(pos1.getYPos(), y0);
    std::tuple<double, double, bool> tuple {x0 - p90_width * HALF, x0 + p90_width * HALF, true};
    ASSERT_EQ(pos1.getXArea(), tuple);

}
TEST(soldier_test, Test11MoveWithCollisionGoingDown) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,SOLDIER_2);
    std::shared_ptr<Soldier> soldier2 = sfactory.create(2,SOLDIER_2);
    double x0 = 13.0;
    double y0 = 20.0;
    double x0_2 = x0;
    double y0_2 = y0 - p90_height - 1;
    Position pos(x0, y0, soldier->getWidth(), soldier->getHeight(), MAP_DIM, MAP_DIM);
    Position pos2(x0_2, y0_2, soldier2->getWidth(), soldier2->getHeight(), MAP_DIM, MAP_DIM);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    ASSERT_NO_THROW(soldier2->setPosition(std::move(pos2)));
    soldiers.emplace(2, std::move(soldier2));
    soldier->move(ON, Y, DOWN, NORMAL);
    double time = 1.0;
    soldier->simulateMove(time, std::chrono::steady_clock::now(), std::ref(soldiers), std::ref(zombies), MAP_DIM, MAP_DIM);
    Position& pos1 = soldier->getPosition();
    ASSERT_EQ(pos1.getYPos(), y0);
    ASSERT_EQ(pos1.getXPos(), x0);
    std::tuple<double, double, bool> tuple {y0 - p90_height * HALF, y0 + p90_height * HALF, true};
    ASSERT_EQ(pos1.getYArea(), tuple);

}

TEST(soldier_test, Test12MoveWithCollisionGoingUp) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,SOLDIER_2);
    std::shared_ptr<Soldier> soldier2 = sfactory.create(2,SOLDIER_2);
    double x0 = 13.0;
    double y0_2 = 20.0;
    double x0_2 = 13.0;
    double y0 = 13.0;
    Position pos(x0, y0, soldier->getWidth(), soldier->getHeight(), MAP_DIM, MAP_DIM);
    Position pos2(x0_2, y0_2, soldier2->getWidth(), soldier2->getHeight(), MAP_DIM, MAP_DIM);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    ASSERT_NO_THROW(soldier2->setPosition(std::move(pos2)));
    soldiers.emplace(2, std::move(soldier2));
    soldier->move(ON, Y, UP, NORMAL);
    double time = 1.0;
    soldier->simulateMove(time, std::chrono::steady_clock::now(), std::ref(soldiers), std::ref(zombies), MAP_DIM, MAP_DIM);
    Position& pos1 = soldier->getPosition();
    ASSERT_EQ(pos1.getYPos(), 13.0);
    ASSERT_EQ(pos1.getXPos(), x0);
    std::tuple<double, double, bool> tuple {10.0, 16.0, true};
    ASSERT_EQ(pos1.getYArea(), tuple);

}

TEST(soldier_test, Test13SetPositionOnMaxXLimitToSoldier) {
    SoldierFactory sfactory;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,SOLDIER_2);
    Position pos(MAP_DIM, 10.0, soldier->getWidth(), soldier->getHeight(), MAP_DIM, MAP_DIM);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    Position& pos1 = soldier->getPosition();
    ASSERT_EQ(pos1.getXPos(), MAP_DIM);
    ASSERT_EQ(pos1.getYPos(), 10.0);
    std::tuple<double, double, bool> tuple {0.0, 99.0, false};
    ASSERT_EQ(pos1.getXArea(), tuple);

}

TEST(soldier_test, Test14SetPositionOnMinXLimitToSoldier) {
    SoldierFactory sfactory;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,SOLDIER_2);
    Position pos(0.0, 10.0, soldier->getWidth(), soldier->getHeight(), MAP_DIM, MAP_DIM);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    Position& pos1 = soldier->getPosition();
    ASSERT_EQ(pos1.getXPos(), 0.0);
    ASSERT_EQ(pos1.getYPos(), 10.0);
    std::tuple<double, double, bool> tuple {1.0, MAP_DIM, false};
    ASSERT_EQ(pos1.getXArea(), tuple);

}

TEST(soldier_test, Test15SetPositionOnMinYLimitToSoldier) {
    SoldierFactory sfactory;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,SOLDIER_2);
    Position pos(20.0, 0.0, soldier->getWidth(), soldier->getHeight(), MAP_DIM, MAP_DIM);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    Position& pos1 = soldier->getPosition();
    ASSERT_EQ(pos1.getXPos(), 20.0);
    ASSERT_EQ(pos1.getYPos(), 0.0);
    std::tuple<double, double, bool> tuple {3.0, 98.0, false};
    ASSERT_EQ(pos1.getYArea(), tuple);

}

TEST(soldier_test, Test16SetPositionOnMaxYLimitToSoldier) {
    SoldierFactory sfactory;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,SOLDIER_2);
    Position pos(20.0, MAP_DIM, soldier->getWidth(), soldier->getHeight(), MAP_DIM, MAP_DIM);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    Position& pos1 = soldier->getPosition();
    ASSERT_EQ(pos1.getXPos(), 20.0);
    ASSERT_EQ(pos1.getYPos(), MAP_DIM);
    std::tuple<double, double, bool> tuple {2.0, 97.0, false};
    ASSERT_EQ(pos1.getYArea(), tuple);

}

TEST(soldier_test, Test17MoveWithCollisionOnRightWithComplementPosition) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,SOLDIER_2);
    std::shared_ptr<Soldier> soldier2 = sfactory.create(2,SOLDIER_2);
    double x0 = 97.0;
    double y0 = 10.0;
    double x0_2 = MAP_DIM;
    double y0_2 = 10.0;
    Position pos(x0, y0, soldier->getWidth(), soldier->getHeight(), MAP_DIM, MAP_DIM);
    Position pos2(x0_2, y0_2, soldier2->getWidth(), soldier2->getHeight(), MAP_DIM, MAP_DIM);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    ASSERT_NO_THROW(soldier2->setPosition(std::move(pos2)));
    soldiers.emplace(2, std::move(soldier2));
    soldier->move(ON, X, RIGHT, NORMAL);
    double time = 1.0;
    soldier->simulateMove(time, std::chrono::steady_clock::now(), std::ref(soldiers), std::ref(zombies), MAP_DIM, MAP_DIM);
    Position& pos1 = soldier->getPosition();
    ASSERT_EQ(pos1.getXPos(), 97.0);
    ASSERT_EQ(pos1.getYPos(), y0);
    std::tuple<double, double, bool> tuple {96.0, 98.0, true};
    ASSERT_EQ(pos1.getXArea(), tuple);

}

TEST(soldier_test, Test18MoveWithCollisionOnLeftWithComplementPosition) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,SOLDIER_2);
    std::shared_ptr<Soldier> soldier2 = sfactory.create(2,SOLDIER_2);
    double x0 = 2.0;
    double y0 = 10.0;
    double x0_2 = MAP_DIM;
    double y0_2 = 10.0;
    Position pos(x0, y0, soldier->getWidth(), soldier->getHeight(), MAP_DIM, MAP_DIM);
    Position pos2(x0_2, y0_2, soldier2->getWidth(), soldier2->getHeight(), MAP_DIM, MAP_DIM);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    ASSERT_NO_THROW(soldier2->setPosition(std::move(pos2)));
    soldiers.emplace(2, std::move(soldier2));
    soldier->move(ON, X, LEFT, NORMAL);
    double time = 1.0;
    soldier->simulateMove(time, std::chrono::steady_clock::now(), std::ref(soldiers), std::ref(zombies), MAP_DIM, MAP_DIM);
    Position& pos1 = soldier->getPosition();
    ASSERT_EQ(pos1.getXPos(), 2.0);
    ASSERT_EQ(pos1.getYPos(), y0);
    std::tuple<double, double, bool> tuple {1.0, 3.0, true};
    ASSERT_EQ(pos1.getXArea(), tuple);

}

TEST(soldier_test, Test19MoveWithNoCollisionOnRight) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,SOLDIER_2);
    std::shared_ptr<Soldier> soldier2 = sfactory.create(2,SOLDIER_2);
    double x0 = 7.0;
    double y0 = 10.0;
    double x0_2 = 10.0;
    double y0_2 = 30.0;
    Position pos(x0, y0, soldier->getWidth(), soldier->getHeight(), MAP_DIM, MAP_DIM);
    Position pos2(x0_2, y0_2, soldier2->getWidth(), soldier2->getHeight(), MAP_DIM, MAP_DIM);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    ASSERT_NO_THROW(soldier2->setPosition(std::move(pos2)));
    soldiers.emplace(2, std::move(soldier2));
    soldier->move(ON, X, RIGHT, NORMAL);
    double time = 10.0;
    soldier->simulateMove(time, std::chrono::steady_clock::now(), std::ref(soldiers), std::ref(zombies), MAP_DIM, MAP_DIM);
    Position& pos1 = soldier->getPosition();
    ASSERT_EQ(pos1.getXPos(), 17.0);
    ASSERT_EQ(pos1.getYPos(), y0);
    std::tuple<double, double, bool> tuple {16.0, 18.0, true};
    ASSERT_EQ(pos1.getXArea(), tuple);

}

TEST(soldier_test, Test20MoveWithNoCollisionOnRight) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,SOLDIER_2);
    std::shared_ptr<Soldier> soldier2 = sfactory.create(2,SOLDIER_2);
    double x0 = 7.0;
    double y0 = 10.0;
    double x0_2 = 11.0;
    double y0_2 = 10.0;
    Position pos(x0, y0, soldier->getWidth(), soldier->getHeight(), MAP_DIM, MAP_DIM);
    Position pos2(x0_2, y0_2, soldier2->getWidth(), soldier2->getHeight(), MAP_DIM, MAP_DIM);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    ASSERT_NO_THROW(soldier2->setPosition(std::move(pos2)));
    soldiers.emplace(2, std::move(soldier2));
    soldier->move(ON, X, RIGHT, NORMAL);
    double time = 1.0;
    soldier->simulateMove(time, std::chrono::steady_clock::now(), std::ref(soldiers), std::ref(zombies), MAP_DIM, MAP_DIM);
    Position& pos1 = soldier->getPosition();
    ASSERT_EQ(pos1.getXPos(), 8.0);
    ASSERT_EQ(pos1.getYPos(), y0);
    std::tuple<double, double, bool> tuple {7.0, 9.0, true};
    ASSERT_EQ(pos1.getXArea(), tuple);

}


TEST(soldier_test, Test21MoveOnLimit) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,SOLDIER_2);
    double x0 = 0.0;
    double y0 = 10.0;
    Position pos(x0, y0, soldier->getWidth(), soldier->getHeight(), MAP_DIM, MAP_DIM);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    soldier->move(ON, X, LEFT, NORMAL);
    double time = 1.0;
    soldier->simulateMove(time, std::chrono::steady_clock::now(), std::ref(soldiers), std::ref(zombies), MAP_DIM, MAP_DIM);
    Position& pos1 = soldier->getPosition();
    ASSERT_EQ(pos1.getXPos(), MAP_DIM);
    ASSERT_EQ(pos1.getYPos(), y0);
    std::tuple<double, double, bool> tuple {0.0, 99.0, false};
    ASSERT_EQ(pos1.getXArea(), tuple);

}

TEST(soldier_test, Test22MoveWithNoCollisionOnLimit) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,SOLDIER_2);
    std::shared_ptr<Soldier> soldier2 = sfactory.create(2,SOLDIER_2);
    double x0 = 0.0;
    double y0 = 10.0;
    double x0_2 = 50.0;
    double y0_2 = 10.0;
    Position pos(x0, y0, soldier->getWidth(), soldier->getHeight(), MAP_DIM, MAP_DIM);
    Position pos2(x0_2, y0_2, soldier2->getWidth(), soldier2->getHeight(), MAP_DIM, MAP_DIM);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    ASSERT_NO_THROW(soldier2->setPosition(std::move(pos2)));
    soldiers.emplace(2, std::move(soldier2));
    soldier->move(ON, X, LEFT, NORMAL);
    double time = 1.0;
    soldier->simulateMove(time, std::chrono::steady_clock::now(), std::ref(soldiers), std::ref(zombies), MAP_DIM, MAP_DIM);
    Position& pos1 = soldier->getPosition();
    ASSERT_EQ(pos1.getXPos(), MAP_DIM);
    ASSERT_EQ(pos1.getYPos(), y0);
    std::tuple<double, double, bool> tuple {0.0, 99.0, false};
    ASSERT_EQ(pos1.getXArea(), tuple);

}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}