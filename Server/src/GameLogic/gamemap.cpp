#include "../../include/GameLogic/gamemap.h"

GameMap::GameMap(uint32_t x_dimension, uint32_t y_dimension) :
    collision_zones(),
    x_dimension(x_dimension),
    y_dimension(y_dimension) {
        for (uint32_t y = 0; y < y_dimension; y++) {
        std::vector<std::unique_ptr<CollisionZone>> row;
        collision_zones.emplace_back(std::move(row));
        for (uint32_t x = 0; x < x_dimension; x++) {
            std::unique_ptr<CollisionZone> czptr(new CollisionZone());
            (collision_zones[y]).emplace_back(std::move(czptr));
        }
    }
}

uint32_t GameMap::get_x_limit(void) {
    return x_dimension;
}
uint32_t GameMap::get_y_limit(void) {
    return y_dimension;
}

std::unique_ptr<CollisionZone>& GameMap::getCollisionZone(uint32_t x, uint32_t y) {
    // unique_ptr<CollisionZone> cznullptr(nullptr);
    // if ((x >= x_dimension) || (y >= y_dimension)) return (std::ref(cznullptr));
    std::unique_ptr<CollisionZone> &cz = collision_zones.at(x).at(y);
    return cz;
}
std::vector<std::unique_ptr<CollisionZone>>& GameMap::getCollisionZoneRow(uint32_t x) {
    return collision_zones.at(x);
}
