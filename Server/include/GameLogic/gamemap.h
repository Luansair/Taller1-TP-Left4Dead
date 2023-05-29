#ifndef GAMEMAP_H_
#define GAMEMAP_H_

#include "collisionzone.h"

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

// class CollisionZone;

class GameMap {
private:
    vector<vector<unique_ptr<CollisionZone>>> collision_zones; // lista de listas
    uint32_t x_dimension;
    uint32_t y_dimension;

public:
    explicit GameMap(uint32_t x_dimension, uint32_t y_dimension);

    uint32_t get_x_limit(void);
    uint32_t get_y_limit(void);
    unique_ptr<CollisionZone>& getCollisionZone(uint32_t x, uint32_t y);
    vector<unique_ptr<CollisionZone>>& getCollisionZoneRow(uint32_t x);

    GameMap(const GameMap&) = delete;
    GameMap& operator=(const GameMap&) = delete;

    GameMap(GameMap&&) = delete;
    GameMap& operator=(GameMap&&) = delete;
};

#endif  // GAMEMAP_H_
