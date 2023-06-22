#ifndef MATCH_H_
#define MATCH_H_

#include "Soldiers/soldier.h"
#include "Soldiers/soldierfactory.h"
#include "Zombies/zombie.h"
#include "Zombies/zombiefactory.h"
#include "position.h"
#include "match_configurator.h"
#include "../../../Common/include/Information/information_code.h"
#include "../../../Common/include/Information/state_dto_element.h"
#include "../../../Common/include/Information/feedback_server_gamestate.h"

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
public:
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    double x_dim;
    double y_dim;
    uint8_t soldier_counter = 0;
    uint8_t zombie_counter = 0;

    /* Constructor de Match, parámetros: dimensiones del mapa */
    explicit Match(double x_dimension, double y_dimension);

    /* Elimina Soldier del Match, parámetros: id del soldado */
    void delete_soldier(uint32_t soldier_id);
    void delete_zombie(uint32_t zombie_id);

    void delete_dead_soldiers(void);
    void delete_dead_zombies(void);

    /* Agrega Soldier al Match, parámetros: id del soldado, tipo de soldado */
    void join(uint32_t soldier_id, uint8_t soldier_type);

    /* Ejecuta shoot, parámetros: id del soldado que dispara, parámetros shoot */
    void shoot(uint32_t soldier_id, uint8_t state);

    /* Ejecuta revive, parámetros: id del soldado que revive, parámetros revive */
    void revive(uint32_t soldier_id, uint8_t state);

    // /* Ejecuta reload, parámetros: id del soldado que recarga, parámetros reload */
    // void reload(uint32_t soldier_id, uint8_t state);

    /* Ejecuta move, parámetros: id del soldado que se mueve, parámetros move */
    void move(uint32_t soldier_id, 
    uint8_t state,
    uint8_t moveAxis,
    int8_t moveDirection,
    uint8_t moveForce);

    /* Ejecuta throwGrenade, parámetros: id del soldado que tira granada */
    void throwGrenade(uint32_t soldier_id, uint8_t state);

    /* Ejecuta idle, parámetros: id del soldado idle */
    void idle(uint32_t soldier_id, uint8_t state);

    std::map<uint32_t, std::shared_ptr<Soldier>>& getSoldiers(void);

    virtual void simulateStep(std::chrono::_V2::steady_clock::time_point real_time) = 0;
    
    std::vector<std::pair<uint16_t, ElementStateDTO >> getElementStates();

    GameStateFeedback getMatchState(void);

    void setZombie(uint32_t zombie_id, uint8_t zombie_type);

    Match(const Match&) = delete;
    Match& operator=(const Match&) = delete;
};

#endif  // MATCH_H_
