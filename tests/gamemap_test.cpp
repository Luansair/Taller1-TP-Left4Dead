#include <gtest/gtest.h>
#include <typeinfo>
#include "GameLogic/gamemap.h"

TEST(gamemap_test, Test00CreateGameMap) {
    ASSERT_NO_FATAL_FAILURE(GameMap gamemap(0,0));
    ASSERT_NO_FATAL_FAILURE(GameMap gamemap(10,10));
    ASSERT_NO_FATAL_FAILURE(GameMap gamemap(100,100));
    ASSERT_NO_FATAL_FAILURE(GameMap gamemap(1000,1000));
}

TEST(gamemap_test, Test01GetLimits) {

    GameMap gamemap(10, 10);

    uint32_t x = gamemap.get_x_limit();
    uint32_t y = gamemap.get_y_limit();
    ASSERT_EQ(x, 10);
    ASSERT_EQ(y, 10);
}

TEST(gamemap_test, Test02GetCollisionZones) {

    // por ahora lanza excepción si me salgo de rango
    GameMap gamemap(10,10);
    ASSERT_NO_THROW(gamemap.getCollisionZone(0,0));
    ASSERT_NO_THROW(gamemap.getCollisionZone(4,4));
    ASSERT_NO_THROW(gamemap.getCollisionZone(9,9));
    ASSERT_THROW(gamemap.getCollisionZone(10,10), std::out_of_range);
    ASSERT_THROW(gamemap.getCollisionZone(20,20), std::out_of_range);
    
}

TEST(gamemap_test, Test03GetCollisionZonesRow) {

    // por ahora lanza excepción si me salgo de rango
    GameMap gamemap(10,10);
    ASSERT_NO_THROW(gamemap.getCollisionZoneRow(0));
    ASSERT_NO_THROW(gamemap.getCollisionZoneRow(4));
    ASSERT_NO_THROW(gamemap.getCollisionZoneRow(9));
    ASSERT_THROW(gamemap.getCollisionZoneRow(10), std::out_of_range);
    ASSERT_THROW(gamemap.getCollisionZoneRow(20), std::out_of_range);
    
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}