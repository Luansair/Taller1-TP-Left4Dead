#include "../../include/GameLogic/gamemap.h"

GameMap::GameMap(uint32_t x_dimension, uint32_t y_dimension) :
    collision_zones(),
    x_dimension(x_dimension),
    y_dimension(y_dimension) {
        // itero las filas
        for (uint32_t y = 0; y < y_dimension; y++) {
            // les agrego las CollisionZone
            for (uint32_t x = 0; x < x_dimension; x++) {
                CollisionZone* cz = new CollisionZone();
                std::unique_ptr<CollisionZone> czptr(cz);
                (collision_zones[y]).emplace_back(std::move(cz));
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
