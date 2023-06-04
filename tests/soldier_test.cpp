#include <gtest/gtest.h>
#include "GameLogic/Soldiers/soldier.h"
#include "GameLogic/Zombies/zombie.h"
#include "GameLogic/Soldiers/soldierfactory.h"
#include "GameLogic/position.h"

TEST(soldier_test, Test00CreateSoldier) {
    SoldierFactory sfactory;
    ASSERT_NO_FATAL_FAILURE(sfactory.create(P90SOLDIER));
    ASSERT_NO_FATAL_FAILURE(sfactory.create(SCOUTSOLDIER));
    ASSERT_NO_FATAL_FAILURE(sfactory.create(IDFSOLDIER));
}

TEST(soldier_test, Test02SetPositionToSoldier) {
    SoldierFactory sfactory;
    std::shared_ptr<Soldier> soldier = sfactory.create(P90SOLDIER);
    Position pos(10, 10, soldier->getWidth(), soldier->getHeight());
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    Position& pos1 = soldier->getPosition();
    ASSERT_EQ(pos1.getXPos(), 10);
    ASSERT_EQ(pos1.getYPos(), 10);
    ASSERT_EQ(pos1.getXMax(), 11);
    ASSERT_EQ(pos1.getXMin(), 9);
    ASSERT_EQ(pos1.getYMax(), 13);
    ASSERT_EQ(pos1.getYMin(), 7);

}

TEST(soldier_test, Test03MoveSoldierOnXRigth) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(P90SOLDIER);
    int16_t initial_x = 10;
    int16_t initial_y = 10;
    Position pos(initial_x, initial_y, soldier->getWidth(), soldier->getHeight());
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    soldier->move(ON, X, RIGHT, NORMAL);
    uint16_t time = 1;
    soldier->simulateMove(time, std::ref(soldiers), std::ref(zombies));
    Position& pos1 = soldier->getPosition();
    ASSERT_NEAR(pos1.getXPos(), initial_x + time * P90SOLDIERSPEED, 0.5);
    ASSERT_NEAR(pos1.getYPos(), initial_y, 0.5);
    ASSERT_NEAR(pos1.getXMax(), initial_x + time * P90SOLDIERSPEED + P90SOLDIERWIDTH / 2, 0.5);
    ASSERT_NEAR(pos1.getXMin(), initial_x + time * P90SOLDIERSPEED - P90SOLDIERWIDTH / 2, 0.5);
    ASSERT_NEAR(pos1.getYMax(), initial_y + P90SOLDIERHEIGTH / 2, 0.5);
    ASSERT_NEAR(pos1.getYMin(), initial_y - P90SOLDIERHEIGTH / 2, 0.5);

}

TEST(soldier_test, Test04MoveSoldierAWhileOnXRight) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(P90SOLDIER);
    int16_t initial_x = 10;
    int16_t initial_y = 10;
    Position pos(initial_x, initial_y, soldier->getWidth(), soldier->getHeight());
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    soldier->move(ON, X, RIGHT, NORMAL);
    uint16_t time = 10;
    soldier->simulateMove(time, std::ref(soldiers), std::ref(zombies));
    Position& pos1 = soldier->getPosition();
    ASSERT_NEAR(pos1.getXPos(), initial_x + time * P90SOLDIERSPEED, 0.5);
    ASSERT_NEAR(pos1.getYPos(), initial_y, 0.5);
    ASSERT_NEAR(pos1.getXMax(), initial_x + time * P90SOLDIERSPEED + P90SOLDIERWIDTH / 2, 0.5);
    ASSERT_NEAR(pos1.getXMin(), initial_x + time * P90SOLDIERSPEED - P90SOLDIERWIDTH / 2, 0.5);
    ASSERT_NEAR(pos1.getYMax(), initial_y + P90SOLDIERHEIGTH / 2, 0.5);
    ASSERT_NEAR(pos1.getYMin(), initial_y - P90SOLDIERHEIGTH / 2, 0.5);

}

TEST(soldier_test, Test05MoveSoldierOnXLeft) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(P90SOLDIER);
    int16_t initial_x = 10;
    int16_t initial_y = 10;
    Position pos(initial_x, initial_y, soldier->getWidth(), soldier->getHeight());
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    soldier->move(ON, X, LEFT, NORMAL);
    uint16_t time = 1;
    soldier->simulateMove(time, std::ref(soldiers), std::ref(zombies));
    Position& pos1 = soldier->getPosition();
    ASSERT_NEAR(pos1.getXPos(), initial_x - time * P90SOLDIERSPEED, 0.5);
    ASSERT_NEAR(pos1.getYPos(), initial_y, 0.5);
    ASSERT_NEAR(pos1.getXMax(), initial_x - time * P90SOLDIERSPEED + P90SOLDIERWIDTH / 2, 0.5);
    ASSERT_NEAR(pos1.getXMin(), initial_x - time * P90SOLDIERSPEED - P90SOLDIERWIDTH / 2, 0.5);
    ASSERT_NEAR(pos1.getYMax(), initial_y + P90SOLDIERHEIGTH / 2, 0.5);
    ASSERT_NEAR(pos1.getYMin(), initial_y - P90SOLDIERHEIGTH / 2, 0.5);

}

TEST(soldier_test, Test06MoveSoldierAWhileOnXlimit) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(P90SOLDIER);
    int16_t initial_x = 10;
    int16_t initial_y = 10;
    Position pos(initial_x, initial_y, soldier->getWidth(), soldier->getHeight());
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    soldier->move(ON, X, LEFT, NORMAL);
    uint16_t time = 15;
    soldier->simulateMove(time, std::ref(soldiers), std::ref(zombies));
    Position& pos1 = soldier->getPosition();
    ASSERT_NEAR(pos1.getXPos(), P90SOLDIERWIDTH / 2, 0.5);
    ASSERT_NEAR(pos1.getYPos(), initial_y, 0.5);
    ASSERT_NEAR(pos1.getXMax(), P90SOLDIERWIDTH, 0.5);
    ASSERT_NEAR(pos1.getXMin(), 0 , 0.5);
    ASSERT_NEAR(pos1.getYMax(), initial_y + P90SOLDIERHEIGTH / 2, 0.5);
    ASSERT_NEAR(pos1.getYMin(), initial_y - P90SOLDIERHEIGTH / 2, 0.5);

}

TEST(soldier_test, Test07MoveSoldierOnYUp) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(P90SOLDIER);
    int16_t initial_x = 10;
    int16_t initial_y = 10;
    Position pos(initial_x, initial_y, soldier->getWidth(), soldier->getHeight());
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    soldier->move(ON, Y, UP, NORMAL);
    uint16_t time = 1;
    soldier->simulateMove(time, std::ref(soldiers), std::ref(zombies));
    Position& pos1 = soldier->getPosition();
    ASSERT_NEAR(pos1.getXPos(), initial_x, 0.5);
    ASSERT_NEAR(pos1.getYPos(), initial_y + time * P90SOLDIERSPEED, 0.5);
    ASSERT_NEAR(pos1.getXMax(), initial_x + P90SOLDIERWIDTH / 2, 0.5);
    ASSERT_NEAR(pos1.getXMin(), initial_x - P90SOLDIERWIDTH / 2, 0.5);
    ASSERT_NEAR(pos1.getYMax(), initial_y + time * P90SOLDIERSPEED + P90SOLDIERHEIGTH / 2, 0.5);
    ASSERT_NEAR(pos1.getYMin(), initial_y + time * P90SOLDIERSPEED - P90SOLDIERHEIGTH / 2, 0.5);

}

TEST(soldier_test, Test08MoveSoldierOnYDown) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(P90SOLDIER);
    int16_t initial_x = 10;
    int16_t initial_y = 10;
    Position pos(initial_x, initial_y, soldier->getWidth(), soldier->getHeight());
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    soldier->move(ON, Y, DOWN, NORMAL);
    uint16_t time = 1;
    soldier->simulateMove(time, std::ref(soldiers), std::ref(zombies));
    Position& pos1 = soldier->getPosition();
    ASSERT_NEAR(pos1.getXPos(), initial_x, 0.5);
    ASSERT_NEAR(pos1.getYPos(), initial_y - time * P90SOLDIERSPEED, 0.5);
    ASSERT_NEAR(pos1.getXMax(), initial_x + P90SOLDIERWIDTH / 2, 0.5);
    ASSERT_NEAR(pos1.getXMin(), initial_x - P90SOLDIERWIDTH / 2, 0.5);
    ASSERT_NEAR(pos1.getYMax(), initial_y - time * P90SOLDIERSPEED + P90SOLDIERHEIGTH / 2, 0.5);
    ASSERT_NEAR(pos1.getYMin(), initial_y - time * P90SOLDIERSPEED - P90SOLDIERHEIGTH / 2, 0.5);

}

TEST(soldier_test, Test09MoveWithCollisionOnRight) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(P90SOLDIER);
    std::shared_ptr<Soldier> soldier2 = sfactory.create(P90SOLDIER);
    int16_t initial_x = 10;
    int16_t initial_y = 10;
    int16_t initial_x_2 = 30;
    int16_t initial_y_2 = 10;
    Position pos(initial_x, initial_y, soldier->getWidth(), soldier->getHeight());
    Position pos2(initial_x_2, initial_y_2, soldier2->getWidth(), soldier2->getHeight());
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    ASSERT_NO_THROW(soldier2->setPosition(std::move(pos2)));
    soldiers.emplace(2, std::move(soldier2));
    soldier->move(ON, X, RIGHT, NORMAL);
    uint16_t time = 40;
    soldier->simulateMove(time, std::ref(soldiers), std::ref(zombies));
    Position& pos1 = soldier->getPosition();
    ASSERT_EQ(pos1.getXPos(), 27);
    ASSERT_EQ(pos1.getYPos(), initial_y);
    ASSERT_EQ(pos1.getXMax(), 28);
    ASSERT_EQ(pos1.getXMin(), 26);
    ASSERT_EQ(pos1.getYMax(), initial_y + P90SOLDIERHEIGTH / 2);
    ASSERT_EQ(pos1.getYMin(), initial_y - P90SOLDIERHEIGTH / 2);

}

TEST(soldier_test, Test10MoveWithCollisionOnLeft) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(P90SOLDIER);
    std::shared_ptr<Soldier> soldier2 = sfactory.create(P90SOLDIER);
    int16_t initial_x = 20;
    int16_t initial_y = 10;
    int16_t initial_x_2 = 15;
    int16_t initial_y_2 = 10;
    Position pos(initial_x, initial_y, soldier->getWidth(), soldier->getHeight());
    Position pos2(initial_x_2, initial_y_2, soldier2->getWidth(), soldier2->getHeight());
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    ASSERT_NO_THROW(soldier2->setPosition(std::move(pos2)));
    soldiers.emplace(2, std::move(soldier2));
    soldier->move(ON, X, LEFT, NORMAL);
    uint16_t time = 10;
    soldier->simulateMove(time, std::ref(soldiers), std::ref(zombies));
    Position& pos1 = soldier->getPosition();
    ASSERT_EQ(pos1.getXPos(), 18);
    ASSERT_EQ(pos1.getYPos(), initial_y);
    ASSERT_EQ(pos1.getXMax(), 19);
    ASSERT_EQ(pos1.getXMin(), 17);
    ASSERT_EQ(pos1.getYMax(), initial_y + P90SOLDIERHEIGTH / 2);
    ASSERT_EQ(pos1.getYMin(), initial_y - P90SOLDIERHEIGTH / 2);

}

TEST(soldier_test, Test11MoveWithCollisionDown) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(P90SOLDIER);
    std::shared_ptr<Soldier> soldier2 = sfactory.create(P90SOLDIER);
    int16_t initial_x = 15;
    int16_t initial_y = 20;
    int16_t initial_x_2 = 15;
    int16_t initial_y_2 = 10;
    Position pos(initial_x, initial_y, soldier->getWidth(), soldier->getHeight());
    Position pos2(initial_x_2, initial_y_2, soldier2->getWidth(), soldier2->getHeight());
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    ASSERT_NO_THROW(soldier2->setPosition(std::move(pos2)));
    soldiers.emplace(2, std::move(soldier2));
    soldier->move(ON, Y, DOWN, NORMAL);
    uint16_t time = 10;
    soldier->simulateMove(time, std::ref(soldiers), std::ref(zombies));
    Position& pos1 = soldier->getPosition();
    ASSERT_EQ(pos1.getXPos(), initial_x);
    ASSERT_EQ(pos1.getYPos(), 17);
    ASSERT_EQ(pos1.getXMax(), initial_x + 1);
    ASSERT_EQ(pos1.getXMin(), initial_x - 1);
    ASSERT_EQ(pos1.getYMax(), 20);
    ASSERT_EQ(pos1.getYMin(), 14);

}

TEST(soldier_test, Test12MoveWithCollisionUp) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(P90SOLDIER);
    std::shared_ptr<Soldier> soldier2 = sfactory.create(P90SOLDIER);
    int16_t initial_x = 15;
    int16_t initial_y = 5;
    int16_t initial_x_2 = 15;
    int16_t initial_y_2 = 15;
    Position pos(initial_x, initial_y, soldier->getWidth(), soldier->getHeight());
    Position pos2(initial_x_2, initial_y_2, soldier2->getWidth(), soldier2->getHeight());
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    ASSERT_NO_THROW(soldier2->setPosition(std::move(pos2)));
    soldiers.emplace(2, std::move(soldier2));
    soldier->move(ON, Y, UP, NORMAL);
    uint16_t time = 10;
    soldier->simulateMove(time, std::ref(soldiers), std::ref(zombies));
    Position& pos1 = soldier->getPosition();
    ASSERT_EQ(pos1.getXPos(), initial_x);
    ASSERT_EQ(pos1.getYPos(), 8);
    ASSERT_EQ(pos1.getXMax(), initial_x + 1);
    ASSERT_EQ(pos1.getXMin(), initial_x - 1);
    ASSERT_EQ(pos1.getYMax(), 11);
    ASSERT_EQ(pos1.getYMin(), 5);

}

TEST(soldier_test, Test12MoveWithNoCollisionOnRight) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(P90SOLDIER);
    std::shared_ptr<Soldier> soldier2 = sfactory.create(P90SOLDIER);
    int16_t initial_x = 10;
    int16_t initial_y = 10;
    int16_t initial_x_2 = 150;
    int16_t initial_y_2 = 10;
    Position pos(initial_x, initial_y, soldier->getWidth(), soldier->getHeight());
    Position pos2(initial_x_2, initial_y_2, soldier2->getWidth(), soldier2->getHeight());
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    ASSERT_NO_THROW(soldier2->setPosition(std::move(pos2)));
    soldiers.emplace(2, std::move(soldier2));
    soldier->move(ON, X, RIGHT, NORMAL);
    uint16_t time = 10;
    soldier->simulateMove(time, std::ref(soldiers), std::ref(zombies));
    Position& pos1 = soldier->getPosition();
    ASSERT_EQ(pos1.getXPos(), 20);
    ASSERT_EQ(pos1.getYPos(), initial_y);
    ASSERT_EQ(pos1.getXMax(), 21);
    ASSERT_EQ(pos1.getXMin(), 19);
    ASSERT_EQ(pos1.getYMax(), initial_y + P90SOLDIERHEIGTH / 2);
    ASSERT_EQ(pos1.getYMin(), initial_y - P90SOLDIERHEIGTH / 2);

}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}