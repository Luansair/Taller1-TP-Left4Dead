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

/* Class Match para representar una partida del juego.
Tiene un map de soldier_id y punteros a esos Soldier.
Se le pasa el soldier_id y le delega realizar la acción */

class Match {
private:
    // Como no se puede tener un map con una clase abstracta, le pongo punteros.
    std::map<uint32_t, std::unique_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::unique_ptr<Zombie>> zombies;
    GameMap gamemap;

public:

    /* Constructor de Match, parámetros: dimensiones del mapa */
    explicit Match(uint32_t x_dimension, uint32_t y_dimension);

    /* Agrega Soldier al Match, parámetros: id del soldado, puntero al soldado */
    void add_soldier(uint32_t soldier_id, std::unique_ptr<Soldier> &&soldier);

    /* Elimina Soldier del Match, parámetros: id del soldado */
    void delete_soldier(uint32_t soldier_id);

    /* Ejecuta shoot, parámetros: id del soldado que dispara, parámetros shoot */
    void shoot(uint32_t soldier_id, uint8_t state);

    /* Ejecuta reload, parámetros: id del soldado que recarga, parámetros reload */
    void reload(uint32_t soldier_id, uint8_t state);

    /* Ejecuta move, parámetros: id del soldado que se mueve, parámetros move */
    void move(uint32_t soldier_id, 
    uint8_t state,
    uint8_t moveAxis,
    int8_t moveDirection,
    uint8_t moveForce);

    /* Ejecuta cGrenade, parámetros: id del soldado que cambia de granada */
    void cGrenade(uint32_t soldier_id);

    /* Ejecuta throwGrenade, parámetros: id del soldado que tira granada */
    void throwGrenade(uint32_t soldier_id);

    /* Ejecuta idle, parámetros: id del soldado idle */
    void idle(uint32_t soldier_id);

    //simular step
    //dar gamestate

    Match(const Match&) = delete;
    Match& operator=(const Match&) = delete;
};

#endif  // MATCH_H_
