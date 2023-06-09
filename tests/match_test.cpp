#include <gtest/gtest.h>
#include "GameLogic/match.h"
#include "GameLogic/Soldiers/soldierfactory.h"
#include "GameLogic/Soldiers/soldier.h"

TEST(match_test, Test00CreateMatch) {
    ASSERT_NO_FATAL_FAILURE(Match match(0,0));
    ASSERT_NO_FATAL_FAILURE(Match match(10,10));
    ASSERT_NO_FATAL_FAILURE(Match match(100,100));
    ASSERT_NO_FATAL_FAILURE(Match match(1000,100000));
}

TEST(match_test, Test01InserSoldier) {

    Match match(100,100);
    ASSERT_NO_FATAL_FAILURE(match.join(1,1));
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers = match.getSoldiers();
    ASSERT_NO_THROW(soldiers.at(1));

}

TEST(match_test, Test02InsertSomeSoldiers) {

    Match match(100,100);
    ASSERT_NO_FATAL_FAILURE(match.join(1,1));
    ASSERT_NO_FATAL_FAILURE(match.join(2,1));
    ASSERT_NO_FATAL_FAILURE(match.join(3,1));
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers = match.getSoldiers();
    ASSERT_NO_THROW(soldiers.at(1));
    ASSERT_NO_THROW(soldiers.at(2));
    ASSERT_NO_THROW(soldiers.at(3));

}

TEST(match_test, Test03MoveSoldier) {

    Match match(100,100);
    ASSERT_NO_FATAL_FAILURE(match.join(1,1));
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers = match.getSoldiers();
    std::shared_ptr<Soldier> &soldier = soldiers.at(1);
    Position& pos1 = soldier->getPosition();
    ASSERT_EQ(pos1.getXPos(), 1);
    ASSERT_EQ(pos1.getYPos(), 3);
    std::tuple<int16_t, int16_t, bool> tuplex {0, 2, true};
    std::tuple<int16_t, int16_t, bool> tupley {0, 6, true};
    ASSERT_EQ(pos1.getXArea(), tuplex);
    ASSERT_EQ(pos1.getYArea(), tupley);
    match.move(1, ON, X, RIGHT, NORMAL);
    match.simulateStep();
    ASSERT_EQ(pos1.getXPos(), 2);
    ASSERT_EQ(pos1.getYPos(), 3);
    tuplex = {1, 3, true};
    ASSERT_EQ(pos1.getXArea(), tuplex);

}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}