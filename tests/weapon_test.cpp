#include <gtest/gtest.h>
#include "GameLogic/Soldiers/soldier.h"
#include "GameLogic/Zombies/zombie.h"
#include "GameLogic/Soldiers/soldierfactory.h"
#include "GameLogic/Weapons/weaponfactory.h"
#include "GameLogic/position.h"

TEST(weapon_test, Test00CreateWeapon) {
    WeaponFactory wfactory;
    ASSERT_NO_FATAL_FAILURE(wfactory.create(P90WEAPON));
    ASSERT_NO_FATAL_FAILURE(wfactory.create(SCOUTWEAPON));
    ASSERT_NO_FATAL_FAILURE(wfactory.create(IDFWEAPON));
}

TEST(weapon_test, Test01ShootP90) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1, P90SOLDIER);
    std::shared_ptr<Soldier> soldier2 = sfactory.create(2, P90SOLDIER);
    Position pos(10, 10, soldier->getWidth(), soldier->getHeight(),100,100);
    Position pos2(15, 10, soldier2->getWidth(), soldier2->getHeight(),100,100);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    ASSERT_NO_THROW(soldier2->setPosition(std::move(pos2)));
    soldiers.emplace(2, std::move(soldier2));
    soldier->shoot(ON);
    uint16_t time = 10;
    soldier->simulateShoot(time, std::ref(soldiers), std::ref(zombies));
    std::shared_ptr<Soldier> &victim = soldiers.at(2);
    ASSERT_NEAR(victim->getHealth(), P90SOLDIERHEALTH - P90_DAMAGE, 0.5);

}

TEST(weapon_test, Test02ShootP90ToTwoSoldiersInTheSameRow) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1, P90SOLDIER);
    std::shared_ptr<Soldier> soldier2 = sfactory.create(2, P90SOLDIER);
    std::shared_ptr<Soldier> soldier3 = sfactory.create(3, P90SOLDIER);
    Position pos(10, 10, soldier->getWidth(), soldier->getHeight(),100,100);
    Position pos2(15, 10, soldier2->getWidth(), soldier2->getHeight(),100,100);
    Position pos3(20, 10, soldier3->getWidth(), soldier3->getHeight(),100,100);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    ASSERT_NO_THROW(soldier2->setPosition(std::move(pos2)));
    ASSERT_NO_THROW(soldier3->setPosition(std::move(pos3)));
    soldiers.emplace(2, std::move(soldier2));
    soldiers.emplace(3, std::move(soldier3));
    soldier->shoot(ON);
    uint16_t time = 20;
    soldier->simulateShoot(time, std::ref(soldiers), std::ref(zombies));
    std::shared_ptr<Soldier> &victim2 = soldiers.at(2);
    std::shared_ptr<Soldier> &victim3 = soldiers.at(3);
    ASSERT_NEAR(victim2->getHealth(), P90SOLDIERHEALTH - P90_DAMAGE, 0.5);
    ASSERT_NEAR(victim3->getHealth(), P90SOLDIERHEALTH, 0.5);

}

TEST(weapon_test, Test03ShootP90AndMiss) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1, P90SOLDIER);
    std::shared_ptr<Soldier> soldier2 = sfactory.create(2, P90SOLDIER);
    Position pos(100, 10, soldier->getWidth(), soldier->getHeight(),100,100);
    Position pos2(500, 100, soldier2->getWidth(), soldier2->getHeight(),100,100);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    ASSERT_NO_THROW(soldier2->setPosition(std::move(pos2)));
    soldiers.emplace(2, std::move(soldier2));
    soldier->shoot(ON);
    uint16_t time = 10;
    soldier->simulateShoot(time, std::ref(soldiers), std::ref(zombies));
    std::shared_ptr<Soldier> &victim = soldiers.at(2);
    ASSERT_NEAR(victim->getHealth(), P90SOLDIERHEALTH, 0.5);

}

TEST(weapon_test, Test04ShootScout) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1, SCOUTSOLDIER);
    std::shared_ptr<Soldier> soldier2 = sfactory.create(2, P90SOLDIER);
    Position pos(10, 10, soldier->getWidth(), soldier->getHeight(),100,100);
    Position pos2(15, 10, soldier2->getWidth(), soldier2->getHeight(),100,100);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    ASSERT_NO_THROW(soldier2->setPosition(std::move(pos2)));
    soldiers.emplace(2, std::move(soldier2));
    soldier->shoot(ON);
    uint16_t time = 10;
    soldier->simulateShoot(time, std::ref(soldiers), std::ref(zombies));
    std::shared_ptr<Soldier> &victim = soldiers.at(2);
    ASSERT_NEAR(victim->getHealth(), P90SOLDIERHEALTH - SCOUT_DAMAGE, 0.5);

}

TEST(weapon_test, Test05ShootScoutToTwoSoldiersInTheSameRowRight) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1, SCOUTSOLDIER);
    std::shared_ptr<Soldier> soldier2 = sfactory.create(2, P90SOLDIER);
    std::shared_ptr<Soldier> soldier3 = sfactory.create(3, P90SOLDIER);
    Position pos(10, 10, soldier->getWidth(), soldier->getHeight(),100,100);
    Position pos2(15, 10, soldier2->getWidth(), soldier2->getHeight(),100,100);
    Position pos3(20, 10, soldier3->getWidth(), soldier3->getHeight(),100,100);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    ASSERT_NO_THROW(soldier2->setPosition(std::move(pos2)));
    ASSERT_NO_THROW(soldier3->setPosition(std::move(pos3)));
    soldiers.emplace(2, std::move(soldier2));
    soldiers.emplace(3, std::move(soldier3));
    soldier->shoot(ON);
    uint16_t time = 30;
    soldier->simulateShoot(time, std::ref(soldiers), std::ref(zombies));
    std::shared_ptr<Soldier> &victim2 = soldiers.at(2);
    std::shared_ptr<Soldier> &victim3 = soldiers.at(3);
    ASSERT_NEAR(victim2->getHealth(), P90SOLDIERHEALTH - SCOUT_DAMAGE , 0.5);
    ASSERT_NEAR(victim3->getHealth(), P90SOLDIERHEALTH - SCOUT_DAMAGE * DAMAGE_REDUCTION_COEF , 0.5);

}

TEST(weapon_test, Test06ShootScoutToTwoSoldiersInTheSameRowLeft) {
    SoldierFactory sfactory;
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::shared_ptr<Soldier> soldier = sfactory.create(1, SCOUTSOLDIER);
    std::shared_ptr<Soldier> soldier2 = sfactory.create(2, P90SOLDIER);
    std::shared_ptr<Soldier> soldier3 = sfactory.create(3, P90SOLDIER);
    Position pos(20, 10, soldier->getWidth(), soldier->getHeight(),100,100);
    Position pos2(15, 10, soldier2->getWidth(), soldier2->getHeight(),100,100);
    Position pos3(10, 10, soldier3->getWidth(), soldier3->getHeight(),100,100);
    ASSERT_NO_THROW(soldier->setPosition(std::move(pos)));
    ASSERT_NO_THROW(soldier2->setPosition(std::move(pos2)));
    ASSERT_NO_THROW(soldier3->setPosition(std::move(pos3)));
    soldiers.emplace(2, std::move(soldier2));
    soldiers.emplace(3, std::move(soldier3));
    soldier->move(ON, X, LEFT, NORMAL);
    soldier->shoot(ON);
    uint16_t time = 30;
    soldier->simulateMove(1, std::ref(soldiers), std::ref(zombies),100,100);
    soldier->simulateShoot(time, std::ref(soldiers), std::ref(zombies));
    std::shared_ptr<Soldier> &victim2 = soldiers.at(2);
    std::shared_ptr<Soldier> &victim3 = soldiers.at(3);
    ASSERT_NEAR(victim3->getHealth(), P90SOLDIERHEALTH - SCOUT_DAMAGE , 0.5);
    ASSERT_NEAR(victim2->getHealth(), P90SOLDIERHEALTH - SCOUT_DAMAGE * DAMAGE_REDUCTION_COEF , 0.5);

}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}