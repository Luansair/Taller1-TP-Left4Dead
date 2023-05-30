#include <gtest/gtest.h>
#include "GameLogic/collisionzone.h"
#include "GameLogic/gamemap.h"
#include "GameLogic/Soldiers/p90soldier.h"
#include "GameLogic/Weapons/weapon.h"
#include "GameLogic/Grenades/grenade.h"

TEST(collisionzone_test, Test00CreateCollisionZone) {
    ASSERT_NO_FATAL_FAILURE(CollisionZone collisionzone);
    CollisionZone collisionzone;
    ASSERT_FALSE(collisionzone.is_occupied());
}

TEST(collisionzone_test, Test01OccupyCollisionZone) {
    CollisionZone collisionzone;
    std::unique_ptr<Weapon> wptr(nullptr);
    std::unique_ptr<Grenade> gptr(nullptr);
    P90Soldier soldier(100, std::move(wptr), std::move(gptr));
    ASSERT_FALSE(collisionzone.is_occupied());
    ASSERT_TRUE(collisionzone.occupy(&soldier, nullptr));
    ASSERT_TRUE(collisionzone.is_occupied());
}

TEST(collisionzone_test, Test02NotOccupyCollisionZone) {
    CollisionZone collisionzone;
    ASSERT_FALSE(collisionzone.is_occupied());
    ASSERT_FALSE(collisionzone.occupy(nullptr, nullptr));
    ASSERT_FALSE(collisionzone.is_occupied());
}

TEST(collisionzone_test, Test03VacateCollisionZone) {
    CollisionZone collisionzone;
    std::unique_ptr<Weapon> wptr(nullptr);
    std::unique_ptr<Grenade> gptr(nullptr);
    P90Soldier soldier(100, std::move(wptr), std::move(gptr));
    ASSERT_FALSE(collisionzone.is_occupied());
    ASSERT_TRUE(collisionzone.occupy(&soldier, nullptr));
    ASSERT_TRUE(collisionzone.is_occupied());
    collisionzone.vacate();
    ASSERT_FALSE(collisionzone.is_occupied());
}

TEST(collisionzone_test, Test04VacateAndOccupyCollisionZone) {
    CollisionZone collisionzone;
    std::unique_ptr<Weapon> wptr(nullptr);
    std::unique_ptr<Grenade> gptr(nullptr);
    P90Soldier soldier(100, std::move(wptr), std::move(gptr));
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