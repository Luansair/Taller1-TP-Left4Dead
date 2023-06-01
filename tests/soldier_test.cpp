#include <gtest/gtest.h>
#include "GameLogic/collisionzone.h"
#include "GameLogic/gamemap.h"
#include "GameLogic/Soldiers/soldier.h"
#include "GameLogic/Soldiers/p90soldier.h"
#include "GameLogic/Soldiers/scoutsoldier.h"
#include "GameLogic/Soldiers/idfsoldier.h"
#include "GameLogic/Weapons/weapon.h"
#include "GameLogic/Grenades/grenade.h"

TEST(collisionzone_test, Test00CreateSoldier) {
    std::unique_ptr<Weapon> wptr(nullptr);
    std::unique_ptr<Grenade> gptr(nullptr);
    ASSERT_NO_FATAL_FAILURE(P90Soldier psoldier(100, std::move(wptr), std::move(gptr)));
}

TEST(collisionzone_test, Test01SetPosToSoldier) {
    std::unique_ptr<Weapon> wptr(nullptr);
    std::unique_ptr<Grenade> gptr(nullptr);
    P90Soldier psoldier(100, std::move(wptr), std::move(gptr));
    psoldier.setPos(10,10);
    ASSERT_TRUE(psoldier.getXPos() == 10);
    ASSERT_TRUE(psoldier.getYPos() == 10);

}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}