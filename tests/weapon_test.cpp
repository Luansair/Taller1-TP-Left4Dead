#include <gtest/gtest.h>
#include "GameLogic/collisionzone.h"
#include "GameLogic/gamemap.h"
#include "GameLogic/Soldiers/soldier.h"
#include "GameLogic/Soldiers/p90soldier.h"
#include "GameLogic/Soldiers/scoutsoldier.h"
#include "GameLogic/Soldiers/idfsoldier.h"
#include "GameLogic/Soldiers/soldierfactory.h"

#define DAMAGE_REDUCTION_COEF 0.8

TEST(gamemap_test, Test01ShootP90Rigth) {

    GameMap gamemap(10,10);
    SoldierFactory factory;
    std::unique_ptr<Soldier> shooter = factory.create(P90SOLDIER);
    std::unique_ptr<Soldier> victim = factory.create(P90SOLDIER);
    ASSERT_NO_FATAL_FAILURE(gamemap.insertSoldier(shooter.get()));
    ASSERT_NO_FATAL_FAILURE(gamemap.insertSoldier(victim.get()));
    shooter->shoot(std::ref(gamemap), ON);
    ASSERT_NEAR(victim->getHealth(), (P90SOLDIERHEALTH - P90_DAMAGE), 1);
    shooter->shoot(std::ref(gamemap), ON);
    ASSERT_NEAR(victim->getHealth(), (P90SOLDIERHEALTH -  2 * P90_DAMAGE), 1);

}

TEST(gamemap_test, Test02ShootP90Left) {

    GameMap gamemap(10,10);
    SoldierFactory factory;
    std::unique_ptr<Soldier> shooter = factory.create(P90SOLDIER);
    std::unique_ptr<Soldier> victim = factory.create(P90SOLDIER);
    ASSERT_NO_FATAL_FAILURE(gamemap.insertSoldier(victim.get()));
    ASSERT_NO_FATAL_FAILURE(gamemap.insertSoldier(shooter.get()));
    shooter->move(std::ref(gamemap), ON, X, RIGHT, NORMAL);
    shooter->move(std::ref(gamemap), ON, X, RIGHT, NORMAL);
    shooter->move(std::ref(gamemap), ON, X, RIGHT, NORMAL);
    shooter->move(std::ref(gamemap), ON, X, LEFT, NORMAL);
    shooter->shoot(std::ref(gamemap), ON);;
    ASSERT_NEAR(victim->getHealth(), (P90SOLDIERHEALTH - P90_DAMAGE), 1);
    shooter->shoot(std::ref(gamemap), ON);
    ASSERT_NEAR(victim->getHealth(), (P90SOLDIERHEALTH -  2 * P90_DAMAGE), 1);

}

TEST(gamemap_test, Test03ShootP90RigthToTwoSoldiers) {

    GameMap gamemap(10,10);
    SoldierFactory factory;
    std::unique_ptr<Soldier> shooter = factory.create(P90SOLDIER);
    std::unique_ptr<Soldier> victim = factory.create(P90SOLDIER);
    std::unique_ptr<Soldier> not_victim = factory.create(P90SOLDIER);
    ASSERT_NO_FATAL_FAILURE(gamemap.insertSoldier(shooter.get()));
    ASSERT_NO_FATAL_FAILURE(gamemap.insertSoldier(victim.get()));
    ASSERT_NO_FATAL_FAILURE(gamemap.insertSoldier(not_victim.get()));
    shooter->shoot(std::ref(gamemap), ON);
    ASSERT_NEAR(victim->getHealth(), (P90SOLDIERHEALTH - P90_DAMAGE), 1);
    ASSERT_NEAR(not_victim->getHealth(), (P90SOLDIERHEALTH), 1);

}

TEST(gamemap_test, Test04ShootScoutRight) {

    GameMap gamemap(10,10);
    SoldierFactory factory;
    std::unique_ptr<Soldier> shooter = factory.create(SCOUTSOLDIER);
    std::unique_ptr<Soldier> victim1 = factory.create(P90SOLDIER);
    std::unique_ptr<Soldier> victim2 = factory.create(P90SOLDIER);
    std::unique_ptr<Soldier> victim3 = factory.create(P90SOLDIER);
    std::unique_ptr<Soldier> victim4 = factory.create(P90SOLDIER);
    ASSERT_NO_FATAL_FAILURE(gamemap.insertSoldier(shooter.get()));
    ASSERT_NO_FATAL_FAILURE(gamemap.insertSoldier(victim1.get()));
    ASSERT_NO_FATAL_FAILURE(gamemap.insertSoldier(victim2.get()));
    ASSERT_NO_FATAL_FAILURE(gamemap.insertSoldier(victim3.get()));
    ASSERT_NO_FATAL_FAILURE(gamemap.insertSoldier(victim4.get()));
    shooter->shoot(std::ref(gamemap), ON);
    ASSERT_NEAR(victim1->getHealth(), (P90SOLDIERHEALTH - SCOUT_DAMAGE), 1);
    ASSERT_NEAR(victim2->getHealth(), (P90SOLDIERHEALTH - SCOUT_DAMAGE * DAMAGE_REDUCTION_COEF), 1);
    ASSERT_NEAR(victim3->getHealth(), (P90SOLDIERHEALTH - SCOUT_DAMAGE * DAMAGE_REDUCTION_COEF * DAMAGE_REDUCTION_COEF), 1);
    ASSERT_NEAR(victim4->getHealth(), (P90SOLDIERHEALTH - SCOUT_DAMAGE * DAMAGE_REDUCTION_COEF * DAMAGE_REDUCTION_COEF * DAMAGE_REDUCTION_COEF), 1);

}

TEST(gamemap_test, Test05ShootScoutLeft) {

    GameMap gamemap(10,10);
    SoldierFactory factory;
    std::unique_ptr<Soldier> shooter = factory.create(SCOUTSOLDIER);
    std::unique_ptr<Soldier> victim1 = factory.create(P90SOLDIER);
    std::unique_ptr<Soldier> victim2 = factory.create(P90SOLDIER);
    std::unique_ptr<Soldier> victim3 = factory.create(P90SOLDIER);
    std::unique_ptr<Soldier> victim4 = factory.create(P90SOLDIER);
    ASSERT_NO_FATAL_FAILURE(gamemap.insertSoldier(victim1.get()));
    ASSERT_NO_FATAL_FAILURE(gamemap.insertSoldier(victim2.get()));
    ASSERT_NO_FATAL_FAILURE(gamemap.insertSoldier(victim3.get()));
    ASSERT_NO_FATAL_FAILURE(gamemap.insertSoldier(victim4.get()));
    ASSERT_NO_FATAL_FAILURE(gamemap.insertSoldier(shooter.get()));
    shooter->move(std::ref(gamemap), ON, X, RIGHT, NORMAL);
    shooter->move(std::ref(gamemap), ON, X, RIGHT, NORMAL);
    shooter->move(std::ref(gamemap), ON, X, LEFT, NORMAL);
    shooter->shoot(std::ref(gamemap), ON);
    ASSERT_NEAR(victim4->getHealth(), (P90SOLDIERHEALTH - SCOUT_DAMAGE), 1);
    ASSERT_NEAR(victim3->getHealth(), (P90SOLDIERHEALTH - SCOUT_DAMAGE * DAMAGE_REDUCTION_COEF), 1);
    ASSERT_NEAR(victim2->getHealth(), (P90SOLDIERHEALTH - SCOUT_DAMAGE * DAMAGE_REDUCTION_COEF * DAMAGE_REDUCTION_COEF), 1);
    ASSERT_NEAR(victim1->getHealth(), (P90SOLDIERHEALTH - SCOUT_DAMAGE * DAMAGE_REDUCTION_COEF * DAMAGE_REDUCTION_COEF * DAMAGE_REDUCTION_COEF), 1);
}

TEST(gamemap_test, Test06ShootIdfRight) {

    GameMap gamemap(10,10);
    SoldierFactory factory;
    std::unique_ptr<Soldier> shooter = factory.create(IDFSOLDIER);
    std::unique_ptr<Soldier> victim1 = factory.create(P90SOLDIER);
    std::unique_ptr<Soldier> victim2 = factory.create(P90SOLDIER);
    std::unique_ptr<Soldier> victim3 = factory.create(P90SOLDIER);
    std::unique_ptr<Soldier> victim4 = factory.create(P90SOLDIER);
    ASSERT_NO_FATAL_FAILURE(gamemap.insertSoldier(shooter.get()));
    ASSERT_NO_FATAL_FAILURE(gamemap.insertSoldier(victim1.get()));
    ASSERT_NO_FATAL_FAILURE(gamemap.insertSoldier(victim2.get()));
    ASSERT_NO_FATAL_FAILURE(gamemap.insertSoldier(victim3.get()));
    ASSERT_NO_FATAL_FAILURE(gamemap.insertSoldier(victim4.get()));
    shooter->shoot(std::ref(gamemap), ON);
    ASSERT_NEAR(victim1->getHealth(), (P90SOLDIERHEALTH - IDF_DAMAGE), 1);
    victim1->move(std::ref(gamemap), ON, Y, DOWN, NORMAL);
    shooter->shoot(std::ref(gamemap), ON);
    ASSERT_NEAR(victim2->getHealth(), (P90SOLDIERHEALTH - IDF_DAMAGE * DAMAGE_REDUCTION_COEF), 1);
    victim2->move(std::ref(gamemap), ON, Y, DOWN, NORMAL);
    shooter->shoot(std::ref(gamemap), ON);
    ASSERT_NEAR(victim3->getHealth(), (P90SOLDIERHEALTH - IDF_DAMAGE * DAMAGE_REDUCTION_COEF * DAMAGE_REDUCTION_COEF), 1);
    victim3->move(std::ref(gamemap), ON, Y, DOWN, NORMAL);
    shooter->shoot(std::ref(gamemap), ON);
    ASSERT_NEAR(victim4->getHealth(), (P90SOLDIERHEALTH - IDF_DAMAGE * DAMAGE_REDUCTION_COEF * DAMAGE_REDUCTION_COEF * DAMAGE_REDUCTION_COEF), 1);
}

TEST(gamemap_test, Test07ShootIdfLeft) {

    GameMap gamemap(10,10);
    SoldierFactory factory;
    std::unique_ptr<Soldier> shooter = factory.create(IDFSOLDIER);
    std::unique_ptr<Soldier> victim1 = factory.create(P90SOLDIER);
    std::unique_ptr<Soldier> victim2 = factory.create(P90SOLDIER);
    std::unique_ptr<Soldier> victim3 = factory.create(P90SOLDIER);
    std::unique_ptr<Soldier> victim4 = factory.create(P90SOLDIER);
    ASSERT_NO_FATAL_FAILURE(gamemap.insertSoldier(victim1.get()));
    ASSERT_NO_FATAL_FAILURE(gamemap.insertSoldier(victim2.get()));
    ASSERT_NO_FATAL_FAILURE(gamemap.insertSoldier(victim3.get()));
    ASSERT_NO_FATAL_FAILURE(gamemap.insertSoldier(victim4.get()));
    ASSERT_NO_FATAL_FAILURE(gamemap.insertSoldier(shooter.get()));
    shooter->move(std::ref(gamemap), ON, X, RIGHT, NORMAL);
    shooter->move(std::ref(gamemap), ON, X, LEFT, NORMAL);
    shooter->shoot(std::ref(gamemap), ON);
    ASSERT_NEAR(victim4->getHealth(), (P90SOLDIERHEALTH - IDF_DAMAGE), 1);
    victim4->move(std::ref(gamemap), ON, Y, DOWN, NORMAL);
    shooter->shoot(std::ref(gamemap), ON);
    ASSERT_NEAR(victim3->getHealth(), (P90SOLDIERHEALTH - IDF_DAMAGE * DAMAGE_REDUCTION_COEF), 1);
    victim3->move(std::ref(gamemap), ON, Y, DOWN, NORMAL);
    shooter->shoot(std::ref(gamemap), ON);
    ASSERT_NEAR(victim2->getHealth(), (P90SOLDIERHEALTH - IDF_DAMAGE * DAMAGE_REDUCTION_COEF * DAMAGE_REDUCTION_COEF), 1);
    victim2->move(std::ref(gamemap), ON, Y, DOWN, NORMAL);
    shooter->shoot(std::ref(gamemap), ON);
    ASSERT_NEAR(victim1->getHealth(), (P90SOLDIERHEALTH - IDF_DAMAGE * DAMAGE_REDUCTION_COEF * DAMAGE_REDUCTION_COEF * DAMAGE_REDUCTION_COEF), 1);
}

TEST(gamemap_test, Test08ShootIdfLeftDistantVictim) {

    GameMap gamemap(10,10);
    SoldierFactory factory;
    std::unique_ptr<Soldier> shooter = factory.create(IDFSOLDIER);
    std::unique_ptr<Soldier> victim1 = factory.create(P90SOLDIER);
    ASSERT_NO_FATAL_FAILURE(gamemap.insertSoldier(shooter.get()));
    ASSERT_NO_FATAL_FAILURE(gamemap.insertSoldier(victim1.get()));
    victim1->move(std::ref(gamemap), ON, X, RIGHT, NORMAL);
    victim1->move(std::ref(gamemap), ON, X, RIGHT, NORMAL);
    victim1->move(std::ref(gamemap), ON, X, RIGHT, NORMAL);
    shooter->shoot(std::ref(gamemap), ON);
    ASSERT_NEAR(victim1->getHealth(), (P90SOLDIERHEALTH - IDF_DAMAGE * DAMAGE_REDUCTION_COEF * DAMAGE_REDUCTION_COEF * DAMAGE_REDUCTION_COEF), 1);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}