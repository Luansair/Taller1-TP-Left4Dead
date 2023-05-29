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
    uint32_t x_dimension;
    uint32_t y_dimension;

public:

    /* Constructor de GameMap párametros: dimensiones del mapa 2d */
    explicit GameMap(uint32_t x_dimension, uint32_t y_dimension);

    /* getter del límite en eje x (altura) */
    uint32_t get_x_limit(void);

    /* getter del límite en eje y (ancho) */
    uint32_t get_y_limit(void);

    /* getter de una CollisionZone parámetros: coordenadas x,y */
    unique_ptr<CollisionZone>& getCollisionZone(uint32_t x, uint32_t y);

    /* getter del una fila del mapa parámetros: nro fila */
    vector<unique_ptr<CollisionZone>>& getCollisionZoneRow(uint32_t x);

    GameMap(const GameMap&) = delete;
    GameMap& operator=(const GameMap&) = delete;

    GameMap(GameMap&&) = delete;
    GameMap& operator=(GameMap&&) = delete;
};

#endif  // GAMEMAP_H_
