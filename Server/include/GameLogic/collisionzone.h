#ifndef COLLISIONZONE_H_
#define COLLISIONZONE_H_

#include <string>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <map>
#include <vector>
#include <memory>

// forward declarations
class Soldier;
class Zombie;

/* Class CollisionZone, representa las celdas del mapa o la zona de colisión de cada ente del juego */

class CollisionZone {
private:
    uint32_t x_pos;
    uint32_t y_pos;
    bool occupied;
    // bool smoked;
    Soldier* soldier = nullptr;
    Zombie* zombie = nullptr;
    // Crater crater;

public:

    /* Constructor de CollisionZone */
    explicit CollisionZone(uint32_t x, uint32_t y);

    /* Ejecuta la colisión, parámetros: efecto de la colisión (daño) */
    void executeCollision(uint8_t damage);

    /* Retorna si está ocupada o no la celda */
    bool is_occupied(void);

    /* Ocupa la celda con un ente del juego Soldier/Zombie, parámetros: puntero a soldier o zombie */
    /* Solo se debe envíar un puntero, el otro debe ser nullptr porque dos entes no pueden estar en la misma celda */
    bool occupy(Soldier* soldier, Zombie* zombie);

    /* Desocupa la celda */
    void vacate(void);

    /* para testing */
    Soldier* getSoldier(void);

    /* para testing */
    Zombie* getZombie(void);

    CollisionZone(const CollisionZone&) = delete;
    CollisionZone& operator=(const CollisionZone&) = delete;
};

#endif  // COLLISIONZONE_H_
