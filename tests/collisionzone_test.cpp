#include <gtest/gtest.h>
#include "GameLogic/collisionzone.h"
#include "GameLogic/gamemap.h"
#include "GameLogic/Soldiers/soldierfactory.h"
#include "GameLogic/Soldiers/soldier.h"

TEST(collisionzone_test, Test00CreateCollisionZone) {
    ASSERT_NO_FATAL_FAILURE(CollisionZone collisionzone);
    CollisionZone collisionzone;
    ASSERT_FALSE(collisionzone.is_occupied());
    ASSERT_TRUE(collisionzone.getSoldier() == nullptr);
    ASSERT_TRUE(collisionzone.getZombie() == nullptr);
}

TEST(collisionzone_test, Test01OccupyCollisionZone) {
    CollisionZone collisionzone;
    SoldierFactory factory;
    std::unique_ptr<Soldier> soldier = factory.create(1);
    ASSERT_FALSE(collisionzone.is_occupied());
    ASSERT_TRUE(collisionzone.getSoldier() == nullptr);
    ASSERT_TRUE(collisionzone.getZombie() == nullptr);
    ASSERT_TRUE(collisionzone.occupy(soldier.get(), nullptr));
    ASSERT_TRUE(collisionzone.is_occupied());
    ASSERT_TRUE(collisionzone.getSoldier() != nullptr);
    ASSERT_TRUE(collisionzone.getZombie() == nullptr);
}

TEST(collisionzone_test, Test02NotOccupyCollisionZone) {
    CollisionZone collisionzone;
    ASSERT_FALSE(collisionzone.is_occupied());
    ASSERT_TRUE(collisionzone.getSoldier() == nullptr);
    ASSERT_TRUE(collisionzone.getZombie() == nullptr);
    ASSERT_FALSE(collisionzone.occupy(nullptr, nullptr));
    ASSERT_FALSE(collisionzone.is_occupied());
    ASSERT_TRUE(collisionzone.getSoldier() == nullptr);
    ASSERT_TRUE(collisionzone.getZombie() == nullptr);
}

TEST(collisionzone_test, Test03VacateCollisionZone) {
    CollisionZone collisionzone;
    SoldierFactory factory;
    std::unique_ptr<Soldier> soldier = factory.create(1);
    ASSERT_FALSE(collisionzone.is_occupied());
    ASSERT_TRUE(collisionzone.getSoldier() == nullptr);
    ASSERT_TRUE(collisionzone.getZombie() == nullptr);
    ASSERT_TRUE(collisionzone.occupy(soldier.get(), nullptr));
    ASSERT_TRUE(collisionzone.is_occupied());
    ASSERT_TRUE(collisionzone.getSoldier() != nullptr);
    ASSERT_TRUE(collisionzone.getZombie() == nullptr);
    collisionzone.vacate();
    ASSERT_FALSE(collisionzone.is_occupied());
    ASSERT_TRUE(collisionzone.getSoldier() == nullptr);
    ASSERT_TRUE(collisionzone.getZombie() == nullptr);
}

TEST(collisionzone_test, Test04VacateAndOccupyCollisionZone) {
    CollisionZone collisionzone;
    SoldierFactory factory;
    std::unique_ptr<Soldier> soldier = factory.create(1);
    ASSERT_FALSE(collisionzone.is_occupied());
    ASSERT_TRUE(collisionzone.getSoldier() == nullptr);
    ASSERT_TRUE(collisionzone.getZombie() == nullptr);
    ASSERT_TRUE(collisionzone.occupy(soldier.get(), nullptr));
    ASSERT_TRUE(collisionzone.is_occupied());
    ASSERT_TRUE(collisionzone.getSoldier() != nullptr);
    ASSERT_TRUE(collisionzone.getZombie() == nullptr);
    collisionzone.vacate();
    ASSERT_FALSE(collisionzone.is_occupied());
    ASSERT_TRUE(collisionzone.getSoldier() == nullptr);
    ASSERT_TRUE(collisionzone.getZombie() == nullptr);
    ASSERT_TRUE(collisionzone.occupy(soldier.get(), nullptr));
    ASSERT_TRUE(collisionzone.is_occupied());
    ASSERT_TRUE(collisionzone.getSoldier() != nullptr);
    ASSERT_TRUE(collisionzone.getZombie() == nullptr);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}