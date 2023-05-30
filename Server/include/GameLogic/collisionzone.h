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
using namespace std;

// forward declarations
class Soldier;
class Zombie;

/* Class CollisionZone, representa las celdas del mapa o la zona de colisión de cada ente del juego */

class CollisionZone {
private:
    bool occupied;
    // bool smoked;
    Soldier* soldier = nullptr;
    Zombie* zombie = nullptr;
    // Crater crater;

public:

    /* Constructor de CollisionZone */
    CollisionZone(void);

    /* Ejecuta la colisión, parámetros: efecto de la colisión (daño) */
    void executeCollision(uint8_t damage);

    /* Retorna si está ocupada o no la celda */
    bool is_occupied(void);

    /* Ocupa la celda con un ente del juego Soldier/Zombie, parámetros: puntero a soldier o zombie */
    /* Solo se debe envíar un puntero, el otro debe ser nullptr porque dos entes no pueden estar en la misma celda */
    void occupy(Soldier* soldier, Zombie* zombie);

    /* Desocupa la celda */
    void vacate(void);

    CollisionZone(const CollisionZone&) = delete;
    CollisionZone& operator=(const CollisionZone&) = delete;
};

#endif  // COLLISIONZONE_H_
