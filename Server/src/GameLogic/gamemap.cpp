#include "../../include/GameLogic/gamemap.h"

GameMap::GameMap(int32_t x_dimension, int32_t y_dimension) :
    collision_zones(),
    x_dimension(x_dimension),
    y_dimension(y_dimension) {
        for (int32_t y = 0; y < y_dimension; y++) {
            std::vector<std::unique_ptr<CollisionZone>> row;
            collision_zones.emplace_back(std::move(row));
            for (int32_t x = 0; x < x_dimension; x++) {
                std::unique_ptr<CollisionZone> czptr(new CollisionZone(x, y));
                (collision_zones[y]).emplace_back(std::move(czptr));
            }
        }
}

int32_t GameMap::get_x_limit(void) {
    return x_dimension;
}
int32_t GameMap::get_y_limit(void) {
    return y_dimension;
}

std::unique_ptr<CollisionZone>& GameMap::getCollisionZone(int32_t x, int32_t y) {
    // unique_ptr<CollisionZone> cznullptr(nullptr);
    // if ((x >= x_dimension) || (y >= y_dimension)) return (std::ref(cznullptr));
    return collision_zones.at(y).at(x);
}
std::vector<std::unique_ptr<CollisionZone>>& GameMap::getCollisionZoneRow(int32_t y) {
    return collision_zones.at(y);
}

void GameMap::insertSoldier(Soldier* soldier) {
    for (int32_t y = 0; y < y_dimension; y++) {
        for (int32_t x = 0; x < x_dimension; x++) {
            std::unique_ptr<CollisionZone> &cz = collision_zones.at(y).at(x);
            if (cz->is_occupied()) continue;
            cz->occupy(soldier, nullptr);
            return;
        }
    }
    // lanzar excepción de que no se pudo insertar
}
