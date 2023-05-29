#include "../../include/GameLogic/gamemap.h"

GameMap::GameMap(uint32_t x_dimension, uint32_t y_dimension) :
    collision_zones(),
    x_dimension(x_dimension),
    y_dimension(y_dimension) {
        for (uint32_t i = 0; i < x_dimension; i++) {
            for (uint32_t j = 0; j < y_dimension; j++) {
                std::unique_ptr<CollisionZone> cz;
                (collision_zones[i]).emplace_back(std::move(cz));
            }
       } 
}

uint32_t GameMap::get_x_limit(void) {
    return x_dimension;
}
uint32_t GameMap::get_y_limit(void) {
    return y_dimension;
}

unique_ptr<CollisionZone>& GameMap::getCollisionZone(uint32_t x, uint32_t y) {
    unique_ptr<CollisionZone> &cz = collision_zones[x][y];
    return cz;
}
vector<unique_ptr<CollisionZone>>& GameMap::getCollisionZoneRow(uint32_t x) {
    return collision_zones[x];
}
