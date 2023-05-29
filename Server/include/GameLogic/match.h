#ifndef MATCH_H_
#define MATCH_H_

#include "gamemap.h"
#include "Soldiers/soldier.h"
#include "Zombies/zombie.h"

#include <string>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <map>
#include <vector>
#include <memory>
using namespace std;

class Match {
private:
    map<uint32_t, unique_ptr<Soldier>> soldiers;
    vector<Zombie> zombies;
    GameMap gamemap;

public:
    explicit Match(uint32_t x_dimension, uint32_t y_dimension);

    void shoot(uint32_t soldier_id, uint8_t state);

    void reload(uint32_t soldier_id, uint8_t state);

    void move(uint32_t soldier_id, 
    uint8_t state,
    uint8_t moveAxis,
    int8_t moveDirection,
    uint8_t moveForce);

    void cGrenade(uint32_t soldier_id);

    void throwGrenade(uint32_t soldier_id);

    void idle(uint32_t soldier_id);

    Match(const Match&) = delete;
    Match& operator=(const Match&) = delete;

    Match(Match&&) = delete;
    Match& operator=(Match&&) = delete;
};

#endif  // MATCH_H_
