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

/* Class GameMap para representar las posiciones de las entidades en el juego */

/* 
        x0 x1 x2 x3 x4 x5 xn
    y0 |__|__|__|__|__|__|__|
    y1 |__|__|__|__|__|__|__|
    y2 |__|__|__|__|__|__|__|
    y3 |__|__|__|__|__|__|__|
    yn |__|__|__|__|__|__|__| */

class GameMap {
private:
    std::vector<std::vector<std::unique_ptr<CollisionZone>>> collision_zones;
    int32_t x_dimension;
    int32_t y_dimension;

public:
    /* Constructor de GameMap párametros: dimensiones del mapa 2d */
    explicit GameMap(int32_t x_dimension, int32_t y_dimension);

    /* getter del límite en eje x (altura) */
    int32_t get_x_limit(void);

    /* getter del límite en eje y (ancho) */
    int32_t get_y_limit(void);

    /* getter de una CollisionZone parámetros: coordenadas x,y */
    std::unique_ptr<CollisionZone>& getCollisionZone(int32_t x, int32_t y);

    /* getter del una fila del mapa parámetros: nro fila */
    std::vector<std::unique_ptr<CollisionZone>>& getCollisionZoneRow(int32_t y);

    void insertSoldier(Soldier *soldier);

    GameMap(const GameMap&) = delete;
    GameMap& operator=(const GameMap&) = delete;
};

#endif  // GAMEMAP_H_
