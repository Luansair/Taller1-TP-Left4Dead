#include <gtest/gtest.h>
#include "GameLogic/match.h"
#include "GameLogic/Soldiers/soldierfactory.h"
#include "GameLogic/Soldiers/soldier.h"
#include "../Common/include/Information/state_dto_element.h"
#include "../Common/include/Information/information_code.h"
#include <tuple>
#include <chrono>

bool operator==(const ElementStateDTO& lhs, const ElementStateDTO& rhs) {
    return (lhs.type == rhs.type && 
    lhs.action == rhs.action &&
    lhs.direction == rhs.direction &&
    lhs.position_x == rhs.position_x &&
    lhs.position_y == rhs.position_y);
}

TEST(match_test, Test00CreateMatch) {
    ASSERT_NO_FATAL_FAILURE(Match match(0.0,0.0));
    ASSERT_NO_FATAL_FAILURE(Match match(10.0,10.0));
    ASSERT_NO_FATAL_FAILURE(Match match(100.0,100.0));
    ASSERT_NO_FATAL_FAILURE(Match match(1000.0,100000.0));
}

TEST(match_test, Test01InserSoldier) {

    Match match(100,100);
    ASSERT_NO_FATAL_FAILURE(match.join(1,SOLDIER_1));
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers = match.getSoldiers();
    ASSERT_NO_THROW(soldiers.at(1));

}

TEST(match_test, Test02InsertSomeSoldiers) {

    Match match(100,100);
    ASSERT_NO_FATAL_FAILURE(match.join(1,SOLDIER_1));
    ASSERT_NO_FATAL_FAILURE(match.join(2,SOLDIER_1));
    ASSERT_NO_FATAL_FAILURE(match.join(3,SOLDIER_1));
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers = match.getSoldiers();
    ASSERT_NO_THROW(soldiers.at(1));
    ASSERT_NO_THROW(soldiers.at(2));
    ASSERT_NO_THROW(soldiers.at(3));
    std::vector<std::pair<uint16_t, ElementStateDTO>> dtos = match
            .getElementStates();
    int x = soldiers.at(1)->getPosition().getXPos();
    int y = soldiers.at(1)->getPosition().getYPos();
    ElementStateDTO test1 {SOLDIER_1, SOLDIER_1_IDLE, RIGHT, x, y};
    ASSERT_EQ(dtos.at(0).second, test1);
    int x_2 = soldiers.at(2)->getPosition().getXPos();
    int y_2 = soldiers.at(2)->getPosition().getYPos();
    ElementStateDTO test2 {SOLDIER_1, SOLDIER_1_IDLE, RIGHT, x_2, y_2};
    ASSERT_EQ(dtos.at(1).second, test2);
    int x_3 = soldiers.at(3)->getPosition().getXPos();
    int y_3 = soldiers.at(3)->getPosition().getYPos();
    ElementStateDTO test3 {SOLDIER_1, SOLDIER_1_IDLE, RIGHT, x_3, y_3};
    ASSERT_EQ(dtos.at(2).second, test3);
}

TEST(match_test, Test03MoveSoldier) {

    Match match(100,100);
    ASSERT_NO_FATAL_FAILURE(match.join(1,SOLDIER_1));
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers = match.getSoldiers();
    match.move(1, ON, X, RIGHT, NORMAL);
    match.simulateStep(std::chrono::steady_clock::now());
    std::vector<std::pair<uint16_t, ElementStateDTO>> dtos = match
            .getElementStates();
    int x = soldiers.at(1)->getPosition().getXPos();
    int y = soldiers.at(1)->getPosition().getYPos();
    ElementStateDTO test1 {SOLDIER_1, SOLDIER_1_RUN, RIGHT, x, y};
    ASSERT_EQ(dtos.at(0).second, test1);

}

TEST(match_test, Test04MoveSoldierLeft) {

    Match match(100,100);
    ASSERT_NO_FATAL_FAILURE(match.join(1,SOLDIER_1));
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers = match.getSoldiers();
    match.move(1, ON, X, LEFT, NORMAL);
    match.simulateStep(std::chrono::steady_clock::now());
    std::vector<std::pair<uint16_t, ElementStateDTO>> dtos = match
            .getElementStates();
    int x = soldiers.at(1)->getPosition().getXPos();
    int y = soldiers.at(1)->getPosition().getYPos();
    ElementStateDTO test1 {SOLDIER_1, SOLDIER_1_RUN, LEFT, x, y};
    ASSERT_EQ(dtos.at(0).second, test1);

}

TEST(match_test, Test05MoveSoldierDown) {

    Match match(100,100);
    ASSERT_NO_FATAL_FAILURE(match.join(1,SOLDIER_1));
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers = match.getSoldiers();
    match.move(1, ON, Y, DOWN, NORMAL);
    match.simulateStep(std::chrono::steady_clock::now());
    std::vector<std::pair<uint16_t, ElementStateDTO>> dtos = match
            .getElementStates();
    int x = soldiers.at(1)->getPosition().getXPos();
    int y = soldiers.at(1)->getPosition().getYPos();
    ElementStateDTO test1 {SOLDIER_1, SOLDIER_1_RUN, RIGHT, x, y};
    ASSERT_EQ(dtos.at(0).second, test1);

}

TEST(match_test, Test06MoveSoldierUp) {

    Match match(100,100);
    ASSERT_NO_FATAL_FAILURE(match.join(1,SOLDIER_1));
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers = match.getSoldiers();
    match.move(1, ON, Y, UP, NORMAL);
    match.simulateStep(std::chrono::steady_clock::now());
    std::vector<std::pair<uint16_t, ElementStateDTO>> dtos = match
            .getElementStates();
    int x = soldiers.at(1)->getPosition().getXPos();
    int y = soldiers.at(1)->getPosition().getYPos();
    ElementStateDTO test1 {SOLDIER_1, SOLDIER_1_RUN, RIGHT, x, y};
    ASSERT_EQ(dtos.at(0).second, test1);

}

TEST(match_test, Test07MoveAndStop) {

    Match match(100,100);
    ASSERT_NO_FATAL_FAILURE(match.join(1,SOLDIER_1));
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers = match.getSoldiers();
    match.move(1, ON, Y, UP, NORMAL);
    match.simulateStep(std::chrono::steady_clock::now());
    match.idle(1, ON);
    match.simulateStep(std::chrono::steady_clock::now());
    std::vector<std::pair<uint16_t, ElementStateDTO>> dtos = match
            .getElementStates();
    int x = soldiers.at(1)->getPosition().getXPos();
    int y = soldiers.at(1)->getPosition().getYPos();
    ElementStateDTO test1 {SOLDIER_1, SOLDIER_1_IDLE, RIGHT, x, y};
    ASSERT_EQ(dtos.at(0).second, test1);

}

TEST(match_test, Test08Shoot) {

    Match match(100,100);
    ASSERT_NO_FATAL_FAILURE(match.join(1, SOLDIER_1));
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers = match.getSoldiers();
    match.shoot(1, ON);
    match.simulateStep(std::chrono::steady_clock::now());
    std::vector<std::pair<uint16_t, ElementStateDTO>> dtos = match
            .getElementStates();
    int x = soldiers.at(1)->getPosition().getXPos();
    int y = soldiers.at(1)->getPosition().getYPos();
    ElementStateDTO test1 {SOLDIER_1, SOLDIER_1_SHOOT_1, RIGHT, x, y};
    ASSERT_EQ(dtos.at(0).second, test1);

}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}