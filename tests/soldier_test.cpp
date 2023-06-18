#include <gtest/gtest.h>
#include "GameLogic/Soldiers/soldier.h"
#include "GameLogic/Zombies/zombie.h"
#include "GameLogic/Soldiers/soldierfactory.h"
#include "GameLogic/position.h"
#include <tuple>
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

TEST(soldier_test, Test00CreateSoldier) {
    SoldierFactory sfactory;
    ASSERT_NO_FATAL_FAILURE(sfactory.create(1,SOLDIER_2));
    ASSERT_NO_FATAL_FAILURE(sfactory.create(2,SOLDIER_3));
    ASSERT_NO_FATAL_FAILURE(sfactory.create(3,SOLDIER_1));
}

TEST(soldier_test, Test02SetPositionToSoldier) {
    SoldierFactory sfactory;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,SOLDIER_2);
    Position pos(10.0, 10.0, soldier->getWidth(), soldier->getHeight(), 100.0, 100.0);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    Position& pos1 = soldier->getPosition();
    ASSERT_EQ(pos1.getXPos(), 10.0);
    ASSERT_EQ(pos1.getYPos(), 10.0);
    std::tuple<double, double, bool> tuple {9.0, 11.0, true};
    ASSERT_EQ(pos1.getXArea(), tuple);

}

TEST(soldier_test, Test03MoveSoldierOnXRigth) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,SOLDIER_2);
    double initial_x = 10.0;
    double initial_y = 10.0;
    Position pos(initial_x, initial_y, soldier->getWidth(), soldier->getHeight(), 100.0, 100.0);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    soldier->move(ON, X, RIGHT, NORMAL);
    double time = 1.0;
    soldier->simulateMove(time, std::ref(soldiers), std::ref(zombies), 100.0, 100.0);
    Position& pos1 = soldier->getPosition();
    ASSERT_NEAR(pos1.getXPos(), initial_x + time * p90_speed, 0.5);
    ASSERT_NEAR(pos1.getYPos(), initial_y, 0.5);
    std::tuple<double, double, bool> tuple {10.0, 12.0, true};
    ASSERT_EQ(pos1.getXArea(), tuple);

}

TEST(soldier_test, Test04MoveSoldierAWhileOnXRight) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,SOLDIER_2);
    double initial_x = 10.0;
    double initial_y = 10.0;
    Position pos(initial_x, initial_y, soldier->getWidth(), soldier->getHeight(), 100.0, 100.0);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    soldier->move(ON, X, RIGHT, NORMAL);
    double time = 10.0;
    soldier->simulateMove(time, std::ref(soldiers), std::ref(zombies), 100.0, 100.0);
    Position& pos1 = soldier->getPosition();
    ASSERT_NEAR(pos1.getXPos(), initial_x + time * p90_speed, 0.5);
    ASSERT_NEAR(pos1.getYPos(), initial_y, 0.5);
    std::tuple<double, double, bool> tuple {19.0, 21.0, true};
    ASSERT_EQ(pos1.getXArea(), tuple);

}

TEST(soldier_test, Test05MoveSoldierOnXLeft) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,SOLDIER_2);
    double initial_x = 10.0;
    double initial_y = 10.0;
    Position pos(initial_x, initial_y, soldier->getWidth(), soldier->getHeight(), 100.0, 100.0);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    soldier->move(ON, X, LEFT, NORMAL);
    double time = 1.0;
    soldier->simulateMove(time, std::ref(soldiers), std::ref(zombies), 100.0, 100.0);
    Position& pos1 = soldier->getPosition();
    ASSERT_NEAR(pos1.getXPos(), initial_x - time * p90_speed, 0.5);
    ASSERT_NEAR(pos1.getYPos(), initial_y, 0.5);
    std::tuple<double, double, bool> tuple {8.0, 10.0, true};
    ASSERT_EQ(pos1.getXArea(), tuple);

}

TEST(soldier_test, Test06MoveSoldierAWhileOnXleft) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,SOLDIER_2);
    double initial_x = 30.0;
    double initial_y = 30.0;
    Position pos(initial_x, initial_y, soldier->getWidth(), soldier->getHeight(), 100.0, 100.0);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    soldier->move(ON, X, LEFT, NORMAL);
    double time = 15.0;
    soldier->simulateMove(time, std::ref(soldiers), std::ref(zombies), 100.0, 100.0);
    Position& pos1 = soldier->getPosition();
    ASSERT_NEAR(pos1.getXPos(), initial_x - time * p90_speed, 0.5);
    ASSERT_NEAR(pos1.getYPos(), initial_y, 0.5);
    std::tuple<double, double, bool> tuple {14.0, 16.0, true};
    ASSERT_EQ(pos1.getXArea(), tuple);

}

TEST(soldier_test, Test07MoveSoldierOnYUp) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,SOLDIER_2);
    double initial_x = 10.0;
    double initial_y = 10.0;
    Position pos(initial_x, initial_y, soldier->getWidth(), soldier->getHeight(), 100.0, 100.0);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    soldier->move(ON, Y, UP, NORMAL);
    double time = 1.0;
    soldier->simulateMove(time, std::ref(soldiers), std::ref(zombies), 100.0, 100.0);
    Position& pos1 = soldier->getPosition();
    ASSERT_NEAR(pos1.getXPos(), initial_x, 0.5);
    ASSERT_NEAR(pos1.getYPos(), initial_y + time * p90_speed, 0.5);
    std::tuple<double, double, bool> tuple {8.0, 14.0, true};
    ASSERT_EQ(pos1.getYArea(), tuple);

}

TEST(soldier_test, Test08MoveSoldierOnYDown) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,SOLDIER_2);
    double initial_x = 10.0;
    double initial_y = 10.0;
    Position pos(initial_x, initial_y, soldier->getWidth(), soldier->getHeight(), 100.0, 100.0);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    soldier->move(ON, Y, DOWN, NORMAL);
    double time = 1.0;
    soldier->simulateMove(time, std::ref(soldiers), std::ref(zombies), 100.0, 100.0);
    Position& pos1 = soldier->getPosition();
    ASSERT_NEAR(pos1.getXPos(), initial_x, 0.5);
    ASSERT_NEAR(pos1.getYPos(), initial_y - time * p90_speed, 0.5);
    std::tuple<double, double, bool> tuple {6.0, 12.0, true};
    ASSERT_EQ(pos1.getYArea(), tuple);

}

TEST(soldier_test, Test09MoveWithCollisionOnRight) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,SOLDIER_2);
    std::shared_ptr<Soldier> soldier2 = sfactory.create(2,SOLDIER_2);
    double initial_x = 10.0;
    double initial_y = 10.0;
    double initial_x_2 = 13.0;
    double initial_y_2 = 10.0;
    Position pos(initial_x, initial_y, soldier->getWidth(), soldier->getHeight(), 100.0, 100.0);
    Position pos2(initial_x_2, initial_y_2, soldier2->getWidth(), soldier2->getHeight(), 100.0, 100.0);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    ASSERT_NO_THROW(soldier2->setPosition(std::move(pos2)));
    soldiers.emplace(2, std::move(soldier2));
    soldier->move(ON, X, RIGHT, NORMAL);
    double time = 1.0;
    soldier->simulateMove(time, std::ref(soldiers), std::ref(zombies), 100.0, 100.0);
    Position& pos1 = soldier->getPosition();
    ASSERT_EQ(pos1.getXPos(), 10.0);
    ASSERT_EQ(pos1.getYPos(), initial_y);
    std::tuple<double, double, bool> tuple {9.0, 11.0, true};
    ASSERT_EQ(pos1.getXArea(), tuple);

}

TEST(soldier_test, Test10MoveWithCollisionOnLeft) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,SOLDIER_2);
    std::shared_ptr<Soldier> soldier2 = sfactory.create(2,SOLDIER_2);
    double initial_x = 13.0;
    double initial_y = 10.0;
    double initial_x_2 = 10.0;
    double initial_y_2 = 10.0;
    Position pos(initial_x, initial_y, soldier->getWidth(), soldier->getHeight(), 100.0, 100.0);
    Position pos2(initial_x_2, initial_y_2, soldier2->getWidth(), soldier2->getHeight(), 100.0, 100.0);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    ASSERT_NO_THROW(soldier2->setPosition(std::move(pos2)));
    soldiers.emplace(2, std::move(soldier2));
    soldier->move(ON, X, LEFT, NORMAL);
    double time = 1.0;
    soldier->simulateMove(time, std::ref(soldiers), std::ref(zombies), 100.0, 100.0);
    Position& pos1 = soldier->getPosition();
    ASSERT_EQ(pos1.getXPos(), 13.0);
    ASSERT_EQ(pos1.getYPos(), initial_y);
    std::tuple<double, double, bool> tuple {12.0, 14.0, true};
    ASSERT_EQ(pos1.getXArea(), tuple);

}
TEST(soldier_test, Test11MoveWithCollisionGoingDown) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,SOLDIER_2);
    std::shared_ptr<Soldier> soldier2 = sfactory.create(2,SOLDIER_2);
    double initial_x = 13.0;
    double initial_y = 20.0;
    double initial_x_2 = 13.0;
    double initial_y_2 = 13.0;
    Position pos(initial_x, initial_y, soldier->getWidth(), soldier->getHeight(), 100.0, 100.0);
    Position pos2(initial_x_2, initial_y_2, soldier2->getWidth(), soldier2->getHeight(), 100.0, 100.0);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    ASSERT_NO_THROW(soldier2->setPosition(std::move(pos2)));
    soldiers.emplace(2, std::move(soldier2));
    soldier->move(ON, Y, DOWN, NORMAL);
    double time = 1.0;
    soldier->simulateMove(time, std::ref(soldiers), std::ref(zombies), 100.0, 100.0);
    Position& pos1 = soldier->getPosition();
    ASSERT_EQ(pos1.getYPos(), 20.0);
    ASSERT_EQ(pos1.getXPos(), initial_x);
    std::tuple<double, double, bool> tuple {17.0, 23.0, true};
    ASSERT_EQ(pos1.getYArea(), tuple);

}

TEST(soldier_test, Test12MoveWithCollisionGoingUp) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,SOLDIER_2);
    std::shared_ptr<Soldier> soldier2 = sfactory.create(2,SOLDIER_2);
    double initial_x = 13.0;
    double initial_y_2 = 20.0;
    double initial_x_2 = 13.0;
    double initial_y = 13.0;
    Position pos(initial_x, initial_y, soldier->getWidth(), soldier->getHeight(), 100.0, 100.0);
    Position pos2(initial_x_2, initial_y_2, soldier2->getWidth(), soldier2->getHeight(), 100.0, 100.0);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    ASSERT_NO_THROW(soldier2->setPosition(std::move(pos2)));
    soldiers.emplace(2, std::move(soldier2));
    soldier->move(ON, Y, UP, NORMAL);
    double time = 1.0;
    soldier->simulateMove(time, std::ref(soldiers), std::ref(zombies), 100.0, 100.0);
    Position& pos1 = soldier->getPosition();
    ASSERT_EQ(pos1.getYPos(), 13.0);
    ASSERT_EQ(pos1.getXPos(), initial_x);
    std::tuple<double, double, bool> tuple {10.0, 16.0, true};
    ASSERT_EQ(pos1.getYArea(), tuple);

}

TEST(soldier_test, Test13SetPositionOnMaxXLimitToSoldier) {
    SoldierFactory sfactory;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,SOLDIER_2);
    Position pos(100.0, 10.0, soldier->getWidth(), soldier->getHeight(), 100.0, 100.0);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    Position& pos1 = soldier->getPosition();
    ASSERT_EQ(pos1.getXPos(), 100.0);
    ASSERT_EQ(pos1.getYPos(), 10.0);
    std::tuple<double, double, bool> tuple {0.0, 99.0, false};
    ASSERT_EQ(pos1.getXArea(), tuple);

}

TEST(soldier_test, Test14SetPositionOnMinXLimitToSoldier) {
    SoldierFactory sfactory;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,SOLDIER_2);
    Position pos(0.0, 10.0, soldier->getWidth(), soldier->getHeight(), 100.0, 100.0);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    Position& pos1 = soldier->getPosition();
    ASSERT_EQ(pos1.getXPos(), 0.0);
    ASSERT_EQ(pos1.getYPos(), 10.0);
    std::tuple<double, double, bool> tuple {1.0, 100.0, false};
    ASSERT_EQ(pos1.getXArea(), tuple);

}

TEST(soldier_test, Test15SetPositionOnMinYLimitToSoldier) {
    SoldierFactory sfactory;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,SOLDIER_2);
    Position pos(20.0, 0.0, soldier->getWidth(), soldier->getHeight(), 100.0, 100.0);
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
    Position pos(20.0, 100.0, soldier->getWidth(), soldier->getHeight(), 100.0, 100.0);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    Position& pos1 = soldier->getPosition();
    ASSERT_EQ(pos1.getXPos(), 20.0);
    ASSERT_EQ(pos1.getYPos(), 100.0);
    std::tuple<double, double, bool> tuple {2.0, 97.0, false};
    ASSERT_EQ(pos1.getYArea(), tuple);

}

TEST(soldier_test, Test17MoveWithCollisionOnRightWithComplementPosition) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,SOLDIER_2);
    std::shared_ptr<Soldier> soldier2 = sfactory.create(2,SOLDIER_2);
    double initial_x = 97.0;
    double initial_y = 10.0;
    double initial_x_2 = 100.0;
    double initial_y_2 = 10.0;
    Position pos(initial_x, initial_y, soldier->getWidth(), soldier->getHeight(), 100.0, 100.0);
    Position pos2(initial_x_2, initial_y_2, soldier2->getWidth(), soldier2->getHeight(), 100.0, 100.0);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    ASSERT_NO_THROW(soldier2->setPosition(std::move(pos2)));
    soldiers.emplace(2, std::move(soldier2));
    soldier->move(ON, X, RIGHT, NORMAL);
    double time = 1.0;
    soldier->simulateMove(time, std::ref(soldiers), std::ref(zombies), 100.0, 100.0);
    Position& pos1 = soldier->getPosition();
    ASSERT_EQ(pos1.getXPos(), 97.0);
    ASSERT_EQ(pos1.getYPos(), initial_y);
    std::tuple<double, double, bool> tuple {96.0, 98.0, true};
    ASSERT_EQ(pos1.getXArea(), tuple);

}

TEST(soldier_test, Test18MoveWithCollisionOnLeftWithComplementPosition) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,SOLDIER_2);
    std::shared_ptr<Soldier> soldier2 = sfactory.create(2,SOLDIER_2);
    double initial_x = 2.0;
    double initial_y = 10.0;
    double initial_x_2 = 100.0;
    double initial_y_2 = 10.0;
    Position pos(initial_x, initial_y, soldier->getWidth(), soldier->getHeight(), 100.0, 100.0);
    Position pos2(initial_x_2, initial_y_2, soldier2->getWidth(), soldier2->getHeight(), 100.0, 100.0);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    ASSERT_NO_THROW(soldier2->setPosition(std::move(pos2)));
    soldiers.emplace(2, std::move(soldier2));
    soldier->move(ON, X, LEFT, NORMAL);
    double time = 1.0;
    soldier->simulateMove(time, std::ref(soldiers), std::ref(zombies), 100.0, 100.0);
    Position& pos1 = soldier->getPosition();
    ASSERT_EQ(pos1.getXPos(), 2.0);
    ASSERT_EQ(pos1.getYPos(), initial_y);
    std::tuple<double, double, bool> tuple {1.0, 3.0, true};
    ASSERT_EQ(pos1.getXArea(), tuple);

}

TEST(soldier_test, Test19MoveWithNoCollisionOnRight) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,SOLDIER_2);
    std::shared_ptr<Soldier> soldier2 = sfactory.create(2,SOLDIER_2);
    double initial_x = 7.0;
    double initial_y = 10.0;
    double initial_x_2 = 10.0;
    double initial_y_2 = 30.0;
    Position pos(initial_x, initial_y, soldier->getWidth(), soldier->getHeight(), 100.0, 100.0);
    Position pos2(initial_x_2, initial_y_2, soldier2->getWidth(), soldier2->getHeight(), 100.0, 100.0);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    ASSERT_NO_THROW(soldier2->setPosition(std::move(pos2)));
    soldiers.emplace(2, std::move(soldier2));
    soldier->move(ON, X, RIGHT, NORMAL);
    double time = 10.0;
    soldier->simulateMove(time, std::ref(soldiers), std::ref(zombies), 100.0, 100.0);
    Position& pos1 = soldier->getPosition();
    ASSERT_EQ(pos1.getXPos(), 17.0);
    ASSERT_EQ(pos1.getYPos(), initial_y);
    std::tuple<double, double, bool> tuple {16.0, 18.0, true};
    ASSERT_EQ(pos1.getXArea(), tuple);

}

TEST(soldier_test, Test20MoveWithNoCollisionOnRight) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,SOLDIER_2);
    std::shared_ptr<Soldier> soldier2 = sfactory.create(2,SOLDIER_2);
    double initial_x = 7.0;
    double initial_y = 10.0;
    double initial_x_2 = 11.0;
    double initial_y_2 = 10.0;
    Position pos(initial_x, initial_y, soldier->getWidth(), soldier->getHeight(), 100.0, 100.0);
    Position pos2(initial_x_2, initial_y_2, soldier2->getWidth(), soldier2->getHeight(), 100.0, 100.0);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    ASSERT_NO_THROW(soldier2->setPosition(std::move(pos2)));
    soldiers.emplace(2, std::move(soldier2));
    soldier->move(ON, X, RIGHT, NORMAL);
    double time = 1.0;
    soldier->simulateMove(time, std::ref(soldiers), std::ref(zombies), 100.0, 100.0);
    Position& pos1 = soldier->getPosition();
    ASSERT_EQ(pos1.getXPos(), 8.0);
    ASSERT_EQ(pos1.getYPos(), initial_y);
    std::tuple<double, double, bool> tuple {7.0, 9.0, true};
    ASSERT_EQ(pos1.getXArea(), tuple);

}


TEST(soldier_test, Test21MoveOnLimit) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,SOLDIER_2);
    double initial_x = 0.0;
    double initial_y = 10.0;
    Position pos(initial_x, initial_y, soldier->getWidth(), soldier->getHeight(), 100.0, 100.0);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    soldier->move(ON, X, LEFT, NORMAL);
    double time = 1.0;
    soldier->simulateMove(time, std::ref(soldiers), std::ref(zombies), 100.0, 100.0);
    Position& pos1 = soldier->getPosition();
    ASSERT_EQ(pos1.getXPos(), 100.0);
    ASSERT_EQ(pos1.getYPos(), initial_y);
    std::tuple<double, double, bool> tuple {0.0, 99.0, false};
    ASSERT_EQ(pos1.getXArea(), tuple);

}

TEST(soldier_test, Test22MoveWithNoCollisionOnLimit) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,SOLDIER_2);
    std::shared_ptr<Soldier> soldier2 = sfactory.create(2,SOLDIER_2);
    double initial_x = 0.0;
    double initial_y = 10.0;
    double initial_x_2 = 50.0;
    double initial_y_2 = 10.0;
    Position pos(initial_x, initial_y, soldier->getWidth(), soldier->getHeight(), 100.0, 100.0);
    Position pos2(initial_x_2, initial_y_2, soldier2->getWidth(), soldier2->getHeight(), 100.0, 100.0);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    ASSERT_NO_THROW(soldier2->setPosition(std::move(pos2)));
    soldiers.emplace(2, std::move(soldier2));
    soldier->move(ON, X, LEFT, NORMAL);
    double time = 1.0;
    soldier->simulateMove(time, std::ref(soldiers), std::ref(zombies), 100.0, 100.0);
    Position& pos1 = soldier->getPosition();
    ASSERT_EQ(pos1.getXPos(), 100.0);
    ASSERT_EQ(pos1.getYPos(), initial_y);
    std::tuple<double, double, bool> tuple {0.0, 99.0, false};
    ASSERT_EQ(pos1.getXArea(), tuple);

}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}