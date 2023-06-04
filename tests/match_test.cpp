// #include <gtest/gtest.h>
// #include "GameLogic/Soldiers/soldierfactory.h"
// #include "GameLogic/Soldiers/soldier.h"

// TEST(match_test, Test00CreateMatch) {
//     ASSERT_NO_FATAL_FAILURE(GameMap gamemap(0,0));
//     ASSERT_NO_FATAL_FAILURE(GameMap gamemap(10,10));
//     ASSERT_NO_FATAL_FAILURE(GameMap gamemap(100,100));
//     ASSERT_NO_FATAL_FAILURE(GameMap gamemap(1000,1000));
// }

// TEST(match_test, Test01GetLimits) {

//     GameMap gamemap(10, 10);

//     uint32_t x = gamemap.get_x_limit();
//     uint32_t y = gamemap.get_y_limit();
//     ASSERT_EQ(x, 10);
//     ASSERT_EQ(y, 10);
// }

// TEST(match_test, Test02GetCollisionZones) {

//     // por ahora lanza excepción si me salgo de rango
//     GameMap gamemap(10,10);
//     ASSERT_NO_THROW(gamemap.getCollisionZone(0,0));
//     ASSERT_NO_THROW(gamemap.getCollisionZone(4,4));
//     ASSERT_NO_THROW(gamemap.getCollisionZone(9,9));
//     ASSERT_THROW(gamemap.getCollisionZone(10,10), std::out_of_range);
//     ASSERT_THROW(gamemap.getCollisionZone(20,20), std::out_of_range);
    
// }

// TEST(match_test, Test03GetCollisionZonesRow) {

//     // por ahora lanza excepción si me salgo de rango
//     GameMap gamemap(10,10);
//     ASSERT_NO_THROW(gamemap.getCollisionZoneRow(0));
//     ASSERT_NO_THROW(gamemap.getCollisionZoneRow(4));
//     ASSERT_NO_THROW(gamemap.getCollisionZoneRow(9));
//     ASSERT_THROW(gamemap.getCollisionZoneRow(10), std::out_of_range);
//     ASSERT_THROW(gamemap.getCollisionZoneRow(20), std::out_of_range);
    
// }

// TEST(match_test, Test04InserSoldier) {

//     GameMap gamemap(10,10);
//     std::unique_ptr<CollisionZone>& cz = gamemap.getCollisionZone(0,0);
//     std::unique_ptr<CollisionZone>& cz_empty = gamemap.getCollisionZone(1,0);
//     ASSERT_FALSE(cz->is_occupied());
//     ASSERT_FALSE(cz_empty->is_occupied());
//     SoldierFactory factory;
//     std::unique_ptr<Soldier> soldier = factory.create(1);
//     ASSERT_NO_FATAL_FAILURE(gamemap.insertSoldier(soldier.get()));
//     ASSERT_TRUE(cz->is_occupied());
//     ASSERT_TRUE(cz->getSoldier() != nullptr);
//     ASSERT_FALSE(cz_empty->is_occupied());
//     ASSERT_TRUE(cz_empty->getSoldier() == nullptr);

// }

// TEST(match_test, Test05InsertSomeSoldiers) {

//     GameMap gamemap(10,10);
//     std::unique_ptr<CollisionZone>& cz0 = gamemap.getCollisionZone(0,0);
//     std::unique_ptr<CollisionZone>& cz1 = gamemap.getCollisionZone(1,0);
//     std::unique_ptr<CollisionZone>& cz2 = gamemap.getCollisionZone(2,0);
//     std::unique_ptr<CollisionZone>& cz3 = gamemap.getCollisionZone(3,0);
//     std::unique_ptr<CollisionZone>& cz4 = gamemap.getCollisionZone(4,0);
//     ASSERT_FALSE(cz0->is_occupied());
//     ASSERT_FALSE(cz1->is_occupied());
//     ASSERT_FALSE(cz2->is_occupied());
//     ASSERT_FALSE(cz3->is_occupied());
//     ASSERT_FALSE(cz4->is_occupied());
//     SoldierFactory factory;
//     std::unique_ptr<Soldier> soldier = factory.create(1);
//     ASSERT_NO_FATAL_FAILURE(gamemap.insertSoldier(soldier.get()));
//     ASSERT_NO_FATAL_FAILURE(gamemap.insertSoldier(soldier.get()));
//     ASSERT_NO_FATAL_FAILURE(gamemap.insertSoldier(soldier.get()));
//     ASSERT_NO_FATAL_FAILURE(gamemap.insertSoldier(soldier.get()));
//     ASSERT_TRUE(cz0->is_occupied());
//     ASSERT_TRUE(cz1->is_occupied());
//     ASSERT_TRUE(cz2->is_occupied());
//     ASSERT_TRUE(cz3->is_occupied());
//     ASSERT_FALSE(cz4->is_occupied());
//     ASSERT_TRUE(cz0->getSoldier() != nullptr);
//     ASSERT_TRUE(cz1->getSoldier() != nullptr);
//     ASSERT_TRUE(cz2->getSoldier() != nullptr);
//     ASSERT_TRUE(cz3->getSoldier() != nullptr);
//     ASSERT_TRUE(cz4->getSoldier() == nullptr);

// }

// TEST(match_test, Test06MoveSoldierOnXAndBack) {

//     GameMap gamemap(10,10);
//     std::unique_ptr<CollisionZone>& cz0 = gamemap.getCollisionZone(0,0);
//     std::unique_ptr<CollisionZone>& cz1 = gamemap.getCollisionZone(1,0);
//     SoldierFactory factory;
//     std::unique_ptr<Soldier> soldier = factory.create(1);
//     ASSERT_NO_FATAL_FAILURE(gamemap.insertSoldier(soldier.get()));
//     ASSERT_TRUE(cz0->is_occupied());
//     ASSERT_TRUE(cz0->getSoldier() != nullptr);
//     soldier->move(std::ref(gamemap), 1, 0, 1, 1);
//     ASSERT_TRUE(soldier->getYPos() == 0);
//     ASSERT_TRUE(soldier->getXPos() == 1);
//     ASSERT_FALSE(cz0->is_occupied());
//     ASSERT_TRUE(cz0->getSoldier() == nullptr);
//     ASSERT_TRUE(cz1->is_occupied());
//     ASSERT_TRUE(cz1->getSoldier() != nullptr);
//     soldier->move(std::ref(gamemap), 1, 0, -1, 1);
//     ASSERT_TRUE(soldier->getYPos() == 0);
//     ASSERT_TRUE(soldier->getXPos() == 0);
//     ASSERT_FALSE(cz1->is_occupied());
//     ASSERT_TRUE(cz1->getSoldier() == nullptr);
//     ASSERT_TRUE(cz0->is_occupied());
//     ASSERT_TRUE(cz0->getSoldier() != nullptr);

// }

// TEST(match_test, Test07MoveSoldierOnYAndBack) {

//     GameMap gamemap(10,10);
//     std::unique_ptr<CollisionZone>& cz0 = gamemap.getCollisionZone(0,0);
//     std::unique_ptr<CollisionZone>& cz1 = gamemap.getCollisionZone(0,1);
//     SoldierFactory factory;
//     std::unique_ptr<Soldier> soldier = factory.create(1);
//     ASSERT_NO_FATAL_FAILURE(gamemap.insertSoldier(soldier.get()));
//     ASSERT_TRUE(cz0->is_occupied());
//     ASSERT_TRUE(cz0->getSoldier() != nullptr);
//     soldier->move(std::ref(gamemap), 1, 1, -1, 1);
//     ASSERT_TRUE(soldier->getYPos() == 1);
//     ASSERT_TRUE(soldier->getXPos() == 0);
//     ASSERT_FALSE(cz0->is_occupied());
//     ASSERT_TRUE(cz0->getSoldier() == nullptr);
//     ASSERT_TRUE(cz1->is_occupied());
//     ASSERT_TRUE(cz1->getSoldier() != nullptr);
//     soldier->move(std::ref(gamemap), 1, 1, 1, 1);
//     ASSERT_TRUE(soldier->getYPos() == 0);
//     ASSERT_TRUE(soldier->getXPos() == 0);
//     ASSERT_FALSE(cz1->is_occupied());
//     ASSERT_TRUE(cz1->getSoldier() == nullptr);
//     ASSERT_TRUE(cz0->is_occupied());
//     ASSERT_TRUE(cz0->getSoldier() != nullptr);

// }

// TEST(match_test, Test08MoveSoldierOnXSomeCz) {

//     GameMap gamemap(10,10);
//     std::unique_ptr<CollisionZone>& cz0 = gamemap.getCollisionZone(0,0);
//     std::unique_ptr<CollisionZone>& cz1 = gamemap.getCollisionZone(8,0);
//     SoldierFactory factory;
//     std::unique_ptr<Soldier> soldier = factory.create(1);
//     ASSERT_NO_FATAL_FAILURE(gamemap.insertSoldier(soldier.get()));
//     ASSERT_TRUE(cz0->is_occupied());
//     ASSERT_TRUE(cz0->getSoldier() != nullptr);
//     soldier->move(std::ref(gamemap), 1, 0, 1, 1);
//     soldier->move(std::ref(gamemap), 1, 0, 1, 1);
//     soldier->move(std::ref(gamemap), 1, 0, 1, 1);
//     soldier->move(std::ref(gamemap), 1, 0, 1, 1);
//     soldier->move(std::ref(gamemap), 1, 0, 1, 1);
//     soldier->move(std::ref(gamemap), 1, 0, 1, 1);
//     soldier->move(std::ref(gamemap), 1, 0, 1, 1);
//     soldier->move(std::ref(gamemap), 1, 0, 1, 1);
//     ASSERT_TRUE(soldier->getYPos() == 0);
//     ASSERT_TRUE(soldier->getXPos() == 8);
//     ASSERT_FALSE(cz0->is_occupied());
//     ASSERT_TRUE(cz0->getSoldier() == nullptr);
//     ASSERT_TRUE(cz1->is_occupied());
//     ASSERT_TRUE(cz1->getSoldier() != nullptr);

// }

// TEST(match_test, Test09MoveSoldierOnXLimitAndYLimit) {

//     GameMap gamemap(10,10);
//     std::unique_ptr<CollisionZone>& cz0 = gamemap.getCollisionZone(0,0);
//     SoldierFactory factory;
//     std::unique_ptr<Soldier> soldier = factory.create(1);
//     ASSERT_NO_FATAL_FAILURE(gamemap.insertSoldier(soldier.get()));
//     ASSERT_TRUE(cz0->is_occupied());
//     ASSERT_TRUE(cz0->getSoldier() != nullptr);
//     soldier->move(std::ref(gamemap), 1, 0, -1, 1);
//     ASSERT_TRUE(soldier->getYPos() == 0);
//     ASSERT_TRUE(soldier->getXPos() == 0);
//     ASSERT_TRUE(cz0->is_occupied());
//     ASSERT_TRUE(cz0->getSoldier() != nullptr);
//     soldier->move(std::ref(gamemap), 1, 1, 1, 1);
//     ASSERT_TRUE(soldier->getYPos() == 0);
//     ASSERT_TRUE(soldier->getXPos() == 0);
//     ASSERT_TRUE(cz0->is_occupied());
//     ASSERT_TRUE(cz0->getSoldier() != nullptr);

// }

// TEST(match_test, Test10MoveSoldierOnXMaxLim) {

//     GameMap gamemap(10,10);
//     std::unique_ptr<CollisionZone>& cz1 = gamemap.getCollisionZone(9,0);
//     SoldierFactory factory;
//     std::unique_ptr<Soldier> soldier = factory.create(1);
//     ASSERT_NO_FATAL_FAILURE(gamemap.insertSoldier(soldier.get()));
//     soldier->move(std::ref(gamemap), 1, 0, 1, 1);
//     soldier->move(std::ref(gamemap), 1, 0, 1, 1);
//     soldier->move(std::ref(gamemap), 1, 0, 1, 1);
//     soldier->move(std::ref(gamemap), 1, 0, 1, 1);
//     soldier->move(std::ref(gamemap), 1, 0, 1, 1);
//     soldier->move(std::ref(gamemap), 1, 0, 1, 1);
//     soldier->move(std::ref(gamemap), 1, 0, 1, 1);
//     soldier->move(std::ref(gamemap), 1, 0, 1, 1);
//     soldier->move(std::ref(gamemap), 1, 0, 1, 1);
//     soldier->move(std::ref(gamemap), 1, 0, 1, 1);
//     soldier->move(std::ref(gamemap), 1, 0, 1, 1);
//     soldier->move(std::ref(gamemap), 1, 0, 1, 1);
//     ASSERT_TRUE(soldier->getYPos() == 0);
//     ASSERT_TRUE(soldier->getXPos() == 9);
//     ASSERT_TRUE(cz1->is_occupied());
//     ASSERT_TRUE(cz1->getSoldier() != nullptr);

// }

// TEST(match_test, Test11MoveSoldierOnYMaxLim) {

//     GameMap gamemap(10,10);
//     std::unique_ptr<CollisionZone>& cz1 = gamemap.getCollisionZone(0,9);
//     SoldierFactory factory;
//     std::unique_ptr<Soldier> soldier = factory.create(1);
//     ASSERT_NO_FATAL_FAILURE(gamemap.insertSoldier(soldier.get()));
//     soldier->move(std::ref(gamemap), 1, 1, -1, 1);
//     soldier->move(std::ref(gamemap), 1, 1, -1, 1);
//     soldier->move(std::ref(gamemap), 1, 1, -1, 1);
//     soldier->move(std::ref(gamemap), 1, 1, -1, 1);
//     soldier->move(std::ref(gamemap), 1, 1, -1, 1);
//     soldier->move(std::ref(gamemap), 1, 1, -1, 1);
//     soldier->move(std::ref(gamemap), 1, 1, -1, 1);
//     soldier->move(std::ref(gamemap), 1, 1, -1, 1);
//     soldier->move(std::ref(gamemap), 1, 1, -1, 1);
//     soldier->move(std::ref(gamemap), 1, 1, -1, 1);
//     soldier->move(std::ref(gamemap), 1, 1, -1, 1);
//     soldier->move(std::ref(gamemap), 1, 1, -1, 1);
//     ASSERT_TRUE(soldier->getYPos() == 9);
//     ASSERT_TRUE(soldier->getXPos() == 0);
//     ASSERT_TRUE(cz1->is_occupied());
//     ASSERT_TRUE(cz1->getSoldier() != nullptr);

// }

// TEST(match_test, Test12MoveSoldierWithForce) {

//     GameMap gamemap(10,10);
//     std::unique_ptr<CollisionZone>& cz0 = gamemap.getCollisionZone(0,0);
//     std::unique_ptr<CollisionZone>& cz1 = gamemap.getCollisionZone(8,0);
//     SoldierFactory factory;
//     std::unique_ptr<Soldier> soldier = factory.create(1);
//     ASSERT_NO_FATAL_FAILURE(gamemap.insertSoldier(soldier.get()));
//     ASSERT_TRUE(cz0->is_occupied());
//     ASSERT_TRUE(cz0->getSoldier() != nullptr);
//     soldier->move(std::ref(gamemap), 1, 0, 1, 2);
//     soldier->move(std::ref(gamemap), 1, 0, 1, 2);
//     soldier->move(std::ref(gamemap), 1, 0, 1, 2);
//     soldier->move(std::ref(gamemap), 1, 0, 1, 2);
//     ASSERT_TRUE(soldier->getYPos() == 0);
//     ASSERT_TRUE(soldier->getXPos() == 8);
//     ASSERT_FALSE(cz0->is_occupied());
//     ASSERT_TRUE(cz0->getSoldier() == nullptr);
//     ASSERT_TRUE(cz1->is_occupied());
//     ASSERT_TRUE(cz1->getSoldier() != nullptr);

// }

// int main(int argc, char** argv) {
//     ::testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }