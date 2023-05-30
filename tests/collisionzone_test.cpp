#include <gtest/gtest.h>
#include "GameLogic/collisionzone.h"
#include "GameLogic/gamemap.h"
#include "GameLogic/Soldiers/p90soldier.h"
#include "GameLogic/Weapons/weapon.h"
#include "GameLogic/Grenades/grenade.h"

TEST(gamemanager_test, Test00CreateCollisionZone) {
    ASSERT_NO_FATAL_FAILURE(CollisionZone collisionzone);
    CollisionZone collisionzone;
    ASSERT_FALSE(collisionzone.is_occupied());
}

TEST(gamemanager_test, Test01OccupyCollisionZone) {
    CollisionZone collisionzone;
    unique_ptr<Weapon> wptr(nullptr);
    unique_ptr<Grenade> gptr(nullptr);
    P90Soldier soldier(5, 5, 1, 100, std::move(wptr), std::move(gptr));
    ASSERT_FALSE(collisionzone.is_occupied());
    ASSERT_TRUE(collisionzone.occupy(&soldier, nullptr));
    ASSERT_TRUE(collisionzone.is_occupied());
}

TEST(gamemanager_test, Test02NotOccupyCollisionZone) {
    CollisionZone collisionzone;
    ASSERT_FALSE(collisionzone.is_occupied());
    ASSERT_FALSE(collisionzone.occupy(nullptr, nullptr));
    ASSERT_FALSE(collisionzone.is_occupied());
}

TEST(gamemanager_test, Test03VacateCollisionZone) {
    CollisionZone collisionzone;
    unique_ptr<Weapon> wptr(nullptr);
    unique_ptr<Grenade> gptr(nullptr);
    P90Soldier soldier(5, 5, 1, 100, std::move(wptr), std::move(gptr));
    ASSERT_FALSE(collisionzone.is_occupied());
    ASSERT_TRUE(collisionzone.occupy(&soldier, nullptr));
    ASSERT_TRUE(collisionzone.is_occupied());
    collisionzone.vacate();
    ASSERT_FALSE(collisionzone.is_occupied());
}

TEST(gamemanager_test, Test04VacateAndOccupyCollisionZone) {
    CollisionZone collisionzone;
    unique_ptr<Weapon> wptr(nullptr);
    unique_ptr<Grenade> gptr(nullptr);
    P90Soldier soldier(5, 5, 1, 100, std::move(wptr), std::move(gptr));
    ASSERT_FALSE(collisionzone.is_occupied());
    ASSERT_TRUE(collisionzone.occupy(&soldier, nullptr));
    ASSERT_TRUE(collisionzone.is_occupied());
    collisionzone.vacate();
    ASSERT_FALSE(collisionzone.is_occupied());
    ASSERT_TRUE(collisionzone.occupy(&soldier, nullptr));
    ASSERT_TRUE(collisionzone.is_occupied());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}