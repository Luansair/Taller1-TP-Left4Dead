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

TEST(soldier_test, Test00CreateSoldier) {
    SoldierFactory sfactory;
    ASSERT_NO_FATAL_FAILURE(sfactory.create(1,P90SOLDIER));
    ASSERT_NO_FATAL_FAILURE(sfactory.create(2,SCOUTSOLDIER));
    ASSERT_NO_FATAL_FAILURE(sfactory.create(3,IDFSOLDIER));
}

TEST(soldier_test, Test02SetPositionToSoldier) {
    SoldierFactory sfactory;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,P90SOLDIER);
    Position pos(10, 10, soldier->getWidth(), soldier->getHeight(), 100, 100);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    Position& pos1 = soldier->getPosition();
    ASSERT_EQ(pos1.getXPos(), 10);
    ASSERT_EQ(pos1.getYPos(), 10);
    std::tuple<int16_t, int16_t, bool> tuple {9, 11, true};
    ASSERT_EQ(pos1.getXArea(), tuple);

}

TEST(soldier_test, Test03MoveSoldierOnXRigth) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,P90SOLDIER);
    int16_t initial_x = 10;
    int16_t initial_y = 10;
    Position pos(initial_x, initial_y, soldier->getWidth(), soldier->getHeight(), 100, 100);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    soldier->move(ON, X, RIGHT, NORMAL);
    uint16_t time = 1;
    soldier->simulateMove(time, std::ref(soldiers), std::ref(zombies), 100, 100);
    Position& pos1 = soldier->getPosition();
    ASSERT_NEAR(pos1.getXPos(), initial_x + time * p90_speed, 0.5);
    ASSERT_NEAR(pos1.getYPos(), initial_y, 0.5);
    std::tuple<int16_t, int16_t, bool> tuple {10, 12, true};
    ASSERT_EQ(pos1.getXArea(), tuple);

}

TEST(soldier_test, Test04MoveSoldierAWhileOnXRight) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,P90SOLDIER);
    int16_t initial_x = 10;
    int16_t initial_y = 10;
    Position pos(initial_x, initial_y, soldier->getWidth(), soldier->getHeight(), 100, 100);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    soldier->move(ON, X, RIGHT, NORMAL);
    uint16_t time = 10;
    soldier->simulateMove(time, std::ref(soldiers), std::ref(zombies), 100, 100);
    Position& pos1 = soldier->getPosition();
    ASSERT_NEAR(pos1.getXPos(), initial_x + time * p90_speed, 0.5);
    ASSERT_NEAR(pos1.getYPos(), initial_y, 0.5);
    std::tuple<int16_t, int16_t, bool> tuple {19, 21, true};
    ASSERT_EQ(pos1.getXArea(), tuple);

}

TEST(soldier_test, Test05MoveSoldierOnXLeft) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,P90SOLDIER);
    int16_t initial_x = 10;
    int16_t initial_y = 10;
    Position pos(initial_x, initial_y, soldier->getWidth(), soldier->getHeight(), 100, 100);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    soldier->move(ON, X, LEFT, NORMAL);
    uint16_t time = 1;
    soldier->simulateMove(time, std::ref(soldiers), std::ref(zombies), 100, 100);
    Position& pos1 = soldier->getPosition();
    ASSERT_NEAR(pos1.getXPos(), initial_x - time * p90_speed, 0.5);
    ASSERT_NEAR(pos1.getYPos(), initial_y, 0.5);
    std::tuple<int16_t, int16_t, bool> tuple {8, 10, true};
    ASSERT_EQ(pos1.getXArea(), tuple);

}

TEST(soldier_test, Test06MoveSoldierAWhileOnXleft) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,P90SOLDIER);
    int16_t initial_x = 30;
    int16_t initial_y = 30;
    Position pos(initial_x, initial_y, soldier->getWidth(), soldier->getHeight(), 100, 100);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    soldier->move(ON, X, LEFT, NORMAL);
    uint16_t time = 15;
    soldier->simulateMove(time, std::ref(soldiers), std::ref(zombies), 100, 100);
    Position& pos1 = soldier->getPosition();
    ASSERT_NEAR(pos1.getXPos(), initial_x - time * p90_speed, 0.5);
    ASSERT_NEAR(pos1.getYPos(), initial_y, 0.5);
    std::tuple<int16_t, int16_t, bool> tuple {14, 16, true};
    ASSERT_EQ(pos1.getXArea(), tuple);

}

TEST(soldier_test, Test07MoveSoldierOnYUp) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,P90SOLDIER);
    int16_t initial_x = 10;
    int16_t initial_y = 10;
    Position pos(initial_x, initial_y, soldier->getWidth(), soldier->getHeight(), 100, 100);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    soldier->move(ON, Y, UP, NORMAL);
    uint16_t time = 1;
    soldier->simulateMove(time, std::ref(soldiers), std::ref(zombies), 100, 100);
    Position& pos1 = soldier->getPosition();
    ASSERT_NEAR(pos1.getXPos(), initial_x, 0.5);
    ASSERT_NEAR(pos1.getYPos(), initial_y + time * p90_speed, 0.5);
    std::tuple<int16_t, int16_t, bool> tuple {8, 14, true};
    ASSERT_EQ(pos1.getYArea(), tuple);

}

TEST(soldier_test, Test08MoveSoldierOnYDown) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,P90SOLDIER);
    int16_t initial_x = 10;
    int16_t initial_y = 10;
    Position pos(initial_x, initial_y, soldier->getWidth(), soldier->getHeight(), 100, 100);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    soldier->move(ON, Y, DOWN, NORMAL);
    uint16_t time = 1;
    soldier->simulateMove(time, std::ref(soldiers), std::ref(zombies), 100, 100);
    Position& pos1 = soldier->getPosition();
    ASSERT_NEAR(pos1.getXPos(), initial_x, 0.5);
    ASSERT_NEAR(pos1.getYPos(), initial_y - time * p90_speed, 0.5);
    std::tuple<int16_t, int16_t, bool> tuple {6, 12, true};
    ASSERT_EQ(pos1.getYArea(), tuple);

}

TEST(soldier_test, Test09MoveWithCollisionOnRight) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,P90SOLDIER);
    std::shared_ptr<Soldier> soldier2 = sfactory.create(2,P90SOLDIER);
    int16_t initial_x = 10;
    int16_t initial_y = 10;
    int16_t initial_x_2 = 13;
    int16_t initial_y_2 = 10;
    Position pos(initial_x, initial_y, soldier->getWidth(), soldier->getHeight(), 100, 100);
    Position pos2(initial_x_2, initial_y_2, soldier2->getWidth(), soldier2->getHeight(), 100, 100);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    ASSERT_NO_THROW(soldier2->setPosition(std::move(pos2)));
    soldiers.emplace(2, std::move(soldier2));
    soldier->move(ON, X, RIGHT, NORMAL);
    uint16_t time = 1;
    soldier->simulateMove(time, std::ref(soldiers), std::ref(zombies), 100, 100);
    Position& pos1 = soldier->getPosition();
    ASSERT_EQ(pos1.getXPos(), 10);
    ASSERT_EQ(pos1.getYPos(), initial_y);
    std::tuple<int16_t, int16_t, bool> tuple {9, 11, true};
    ASSERT_EQ(pos1.getXArea(), tuple);

}

TEST(soldier_test, Test10MoveWithCollisionOnLeft) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,P90SOLDIER);
    std::shared_ptr<Soldier> soldier2 = sfactory.create(2,P90SOLDIER);
    int16_t initial_x = 13;
    int16_t initial_y = 10;
    int16_t initial_x_2 = 10;
    int16_t initial_y_2 = 10;
    Position pos(initial_x, initial_y, soldier->getWidth(), soldier->getHeight(), 100, 100);
    Position pos2(initial_x_2, initial_y_2, soldier2->getWidth(), soldier2->getHeight(), 100, 100);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    ASSERT_NO_THROW(soldier2->setPosition(std::move(pos2)));
    soldiers.emplace(2, std::move(soldier2));
    soldier->move(ON, X, LEFT, NORMAL);
    uint16_t time = 1;
    soldier->simulateMove(time, std::ref(soldiers), std::ref(zombies), 100, 100);
    Position& pos1 = soldier->getPosition();
    ASSERT_EQ(pos1.getXPos(), 13);
    ASSERT_EQ(pos1.getYPos(), initial_y);
    std::tuple<int16_t, int16_t, bool> tuple {12, 14, true};
    ASSERT_EQ(pos1.getXArea(), tuple);

}
TEST(soldier_test, Test11MoveWithCollisionGoingDown) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,P90SOLDIER);
    std::shared_ptr<Soldier> soldier2 = sfactory.create(2,P90SOLDIER);
    int16_t initial_x = 13;
    int16_t initial_y = 20;
    int16_t initial_x_2 = 13;
    int16_t initial_y_2 = 13;
    Position pos(initial_x, initial_y, soldier->getWidth(), soldier->getHeight(), 100, 100);
    Position pos2(initial_x_2, initial_y_2, soldier2->getWidth(), soldier2->getHeight(), 100, 100);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    ASSERT_NO_THROW(soldier2->setPosition(std::move(pos2)));
    soldiers.emplace(2, std::move(soldier2));
    soldier->move(ON, Y, DOWN, NORMAL);
    uint16_t time = 1;
    soldier->simulateMove(time, std::ref(soldiers), std::ref(zombies), 100, 100);
    Position& pos1 = soldier->getPosition();
    ASSERT_EQ(pos1.getYPos(), 20);
    ASSERT_EQ(pos1.getXPos(), initial_x);
    std::tuple<int16_t, int16_t, bool> tuple {17, 23, true};
    ASSERT_EQ(pos1.getYArea(), tuple);

}

TEST(soldier_test, Test12MoveWithCollisionGoingUp) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,P90SOLDIER);
    std::shared_ptr<Soldier> soldier2 = sfactory.create(2,P90SOLDIER);
    int16_t initial_x = 13;
    int16_t initial_y_2 = 20;
    int16_t initial_x_2 = 13;
    int16_t initial_y = 13;
    Position pos(initial_x, initial_y, soldier->getWidth(), soldier->getHeight(), 100, 100);
    Position pos2(initial_x_2, initial_y_2, soldier2->getWidth(), soldier2->getHeight(), 100, 100);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    ASSERT_NO_THROW(soldier2->setPosition(std::move(pos2)));
    soldiers.emplace(2, std::move(soldier2));
    soldier->move(ON, Y, UP, NORMAL);
    uint16_t time = 1;
    soldier->simulateMove(time, std::ref(soldiers), std::ref(zombies), 100, 100);
    Position& pos1 = soldier->getPosition();
    ASSERT_EQ(pos1.getYPos(), 13);
    ASSERT_EQ(pos1.getXPos(), initial_x);
    std::tuple<int16_t, int16_t, bool> tuple {10, 16, true};
    ASSERT_EQ(pos1.getYArea(), tuple);

}

TEST(soldier_test, Test13SetPositionOnMaxXLimitToSoldier) {
    SoldierFactory sfactory;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,P90SOLDIER);
    Position pos(100, 10, soldier->getWidth(), soldier->getHeight(), 100, 100);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    Position& pos1 = soldier->getPosition();
    ASSERT_EQ(pos1.getXPos(), 100);
    ASSERT_EQ(pos1.getYPos(), 10);
    std::tuple<int16_t, int16_t, bool> tuple {1, 99, false};
    ASSERT_EQ(pos1.getXArea(), tuple);

}

TEST(soldier_test, Test14SetPositionOnMinYLimitToSoldier) {
    SoldierFactory sfactory;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,P90SOLDIER);
    Position pos(0, 10, soldier->getWidth(), soldier->getHeight(), 100, 100);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    Position& pos1 = soldier->getPosition();
    ASSERT_EQ(pos1.getXPos(), 0);
    ASSERT_EQ(pos1.getYPos(), 10);
    std::tuple<int16_t, int16_t, bool> tuple {1, 99, false};
    ASSERT_EQ(pos1.getXArea(), tuple);

}

TEST(soldier_test, Test15SetPositionOnMinYLimitToSoldier) {
    SoldierFactory sfactory;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,P90SOLDIER);
    Position pos(20, 0, soldier->getWidth(), soldier->getHeight(), 100, 100);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    Position& pos1 = soldier->getPosition();
    ASSERT_EQ(pos1.getXPos(), 20);
    ASSERT_EQ(pos1.getYPos(), 0);
    std::tuple<int16_t, int16_t, bool> tuple {3, 97, false};
    ASSERT_EQ(pos1.getYArea(), tuple);

}

TEST(soldier_test, Test16SetPositionOnMaxYLimitToSoldier) {
    SoldierFactory sfactory;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,P90SOLDIER);
    Position pos(20, 100, soldier->getWidth(), soldier->getHeight(), 100, 100);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    Position& pos1 = soldier->getPosition();
    ASSERT_EQ(pos1.getXPos(), 20);
    ASSERT_EQ(pos1.getYPos(), 100);
    std::tuple<int16_t, int16_t, bool> tuple {3, 97, false};
    ASSERT_EQ(pos1.getYArea(), tuple);

}

TEST(soldier_test, Test17MoveWithCollisionOnRightWithComplementPosition) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,P90SOLDIER);
    std::shared_ptr<Soldier> soldier2 = sfactory.create(2,P90SOLDIER);
    int16_t initial_x = 97;
    int16_t initial_y = 10;
    int16_t initial_x_2 = 100;
    int16_t initial_y_2 = 10;
    Position pos(initial_x, initial_y, soldier->getWidth(), soldier->getHeight(), 100, 100);
    Position pos2(initial_x_2, initial_y_2, soldier2->getWidth(), soldier2->getHeight(), 100, 100);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    ASSERT_NO_THROW(soldier2->setPosition(std::move(pos2)));
    soldiers.emplace(2, std::move(soldier2));
    soldier->move(ON, X, RIGHT, NORMAL);
    uint16_t time = 1;
    soldier->simulateMove(time, std::ref(soldiers), std::ref(zombies), 100, 100);
    Position& pos1 = soldier->getPosition();
    ASSERT_EQ(pos1.getXPos(), 97);
    ASSERT_EQ(pos1.getYPos(), initial_y);
    std::tuple<int16_t, int16_t, bool> tuple {96, 98, true};
    ASSERT_EQ(pos1.getXArea(), tuple);

}

TEST(soldier_test, Test18MoveWithCollisionOnLeftWithComplementPosition) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,P90SOLDIER);
    std::shared_ptr<Soldier> soldier2 = sfactory.create(2,P90SOLDIER);
    int16_t initial_x = 3;
    int16_t initial_y = 10;
    int16_t initial_x_2 = 100;
    int16_t initial_y_2 = 10;
    Position pos(initial_x, initial_y, soldier->getWidth(), soldier->getHeight(), 100, 100);
    Position pos2(initial_x_2, initial_y_2, soldier2->getWidth(), soldier2->getHeight(), 100, 100);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    ASSERT_NO_THROW(soldier2->setPosition(std::move(pos2)));
    soldiers.emplace(2, std::move(soldier2));
    soldier->move(ON, X, LEFT, NORMAL);
    uint16_t time = 1;
    soldier->simulateMove(time, std::ref(soldiers), std::ref(zombies), 100, 100);
    Position& pos1 = soldier->getPosition();
    ASSERT_EQ(pos1.getXPos(), 3);
    ASSERT_EQ(pos1.getYPos(), initial_y);
    std::tuple<int16_t, int16_t, bool> tuple {2, 4, true};
    ASSERT_EQ(pos1.getXArea(), tuple);

}

TEST(soldier_test, Test19MoveWithNoCollisionOnRight) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,P90SOLDIER);
    std::shared_ptr<Soldier> soldier2 = sfactory.create(2,P90SOLDIER);
    int16_t initial_x = 7;
    int16_t initial_y = 10;
    int16_t initial_x_2 = 10;
    int16_t initial_y_2 = 30;
    Position pos(initial_x, initial_y, soldier->getWidth(), soldier->getHeight(), 100, 100);
    Position pos2(initial_x_2, initial_y_2, soldier2->getWidth(), soldier2->getHeight(), 100, 100);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    ASSERT_NO_THROW(soldier2->setPosition(std::move(pos2)));
    soldiers.emplace(2, std::move(soldier2));
    soldier->move(ON, X, RIGHT, NORMAL);
    uint16_t time = 10;
    soldier->simulateMove(time, std::ref(soldiers), std::ref(zombies), 100, 100);
    Position& pos1 = soldier->getPosition();
    ASSERT_EQ(pos1.getXPos(), 17);
    ASSERT_EQ(pos1.getYPos(), initial_y);
    std::tuple<int16_t, int16_t, bool> tuple {16, 18, true};
    ASSERT_EQ(pos1.getXArea(), tuple);

}

TEST(soldier_test, Test20MoveWithNoCollisionOnRight) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1,P90SOLDIER);
    std::shared_ptr<Soldier> soldier2 = sfactory.create(2,P90SOLDIER);
    int16_t initial_x = 7;
    int16_t initial_y = 10;
    int16_t initial_x_2 = 11;
    int16_t initial_y_2 = 10;
    Position pos(initial_x, initial_y, soldier->getWidth(), soldier->getHeight(), 100, 100);
    Position pos2(initial_x_2, initial_y_2, soldier2->getWidth(), soldier2->getHeight(), 100, 100);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    ASSERT_NO_THROW(soldier2->setPosition(std::move(pos2)));
    soldiers.emplace(2, std::move(soldier2));
    soldier->move(ON, X, RIGHT, NORMAL);
    uint16_t time = 1;
    soldier->simulateMove(time, std::ref(soldiers), std::ref(zombies), 100, 100);
    Position& pos1 = soldier->getPosition();
    ASSERT_EQ(pos1.getXPos(), 8);
    ASSERT_EQ(pos1.getYPos(), initial_y);
    std::tuple<int16_t, int16_t, bool> tuple {7, 9, true};
    ASSERT_EQ(pos1.getXArea(), tuple);

}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}