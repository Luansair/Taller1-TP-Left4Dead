#ifndef MATCH_H_
#define MATCH_H_

#include "Soldiers/soldier.h"
#include "Soldiers/soldierfactory.h"
#include "Zombies/zombie.h"
#include "Zombies/zombiefactory.h"
#include "Throwables/throwable.h"
#include "Throwables/throwablesfactory.h"
#include "Throwables/poison.h"
#include "Throwables/grenade_t.h"
#include "position.h"
#include "match_configurator.h"
#include "../../../Common/include/Information/information_code.h"
#include "../../../Common/include/Information/state_dto_element.h"
#include "../../../Common/include/Information/score_dto.h"
#include "../../../Common/include/Information/feedback_server_gamestate.h"
#include "../../../Common/include/Information/feedback_server_score.h"

#include <string>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <map>
#include <vector>
#include <memory>
#include <chrono>
#include <ctime>
#include <fstream>
#include <mutex>

/* Class Match para representar una partida del juego.
Tiene un map de soldier_id y punteros a esos Soldier.
Se le pasa el soldier_id y le delega realizar la acción */

class Match {
public:
    std::map<uint32_t, std::shared_ptr<Soldier>> soldiers;
    std::map<uint32_t, std::shared_ptr<Zombie>> zombies;
    std::map<uint32_t, std::shared_ptr<Throwable>> throwables;
    double x_dim;
    double y_dim;
    uint32_t code;
    uint8_t soldier_counter = 0;
    uint16_t zombie_counter = 0;
    std::chrono::_V2::system_clock::time_point create_time = std::chrono::system_clock::now();
    uint32_t code_counter = 100; // nunca va a haber 100 soldados -> todo ok
    MatchConfigurator configurator;
    ThrowableFactory t_factory;
    bool over = false;
    bool finalizable = false;
    uint8_t dead_soldiers_counter = 0;
    uint16_t dead_zombies_counter = 0;
    std::mutex mtx; // para la carga de scores en el archivo

    /* Constructor de Match, parámetros: dimensiones del mapa */
    explicit Match(double x_dimension, double y_dimension, uint32_t code);

    /* Elimina Soldier del Match, parámetros: id del soldado */
    void delete_soldier(uint32_t soldier_id);
    void delete_zombie(uint32_t zombie_id);

    void delete_dead_soldiers(void);
    void delete_dead_zombies(void);
    void delete_inactive_throwables(void);

    bool verify_over(void);

    void updateScore(uint32_t id, std::shared_ptr<Soldier>& soldier);

    /* Agrega Soldier al Match, parámetros: id del soldado, tipo de soldado */
    void join(uint32_t soldier_id, uint8_t soldier_type);

    /* Ejecuta shoot, parámetros: id del soldado que dispara, parámetros shoot */
    void shoot(uint32_t soldier_id, uint8_t state);

    /* Ejecuta reload, parámetros: id del soldado que recarga, parámetros relaod */
    void reload(uint32_t soldier_id, uint8_t state);

    /* Ejecuta revive, parámetros: id del soldado que revive, parámetros revive */
    void revive(uint32_t soldier_id, uint8_t state);

    /* Ejecuta change_grenade, parámetros: id del soldado que cambia la granada, parámetros on/off */
    void change_grenade(uint32_t soldier_id, uint8_t state);

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

    void killActor(uint32_t soldier_id, uint8_t state);

    std::map<uint32_t, std::shared_ptr<Soldier>>& getSoldiers(void);

    virtual void simulateStep(std::chrono::_V2::system_clock::time_point real_time) = 0;
    
    std::vector<std::pair<uint16_t, ElementStateDTO >> getElementStates();

    GameStateFeedback getMatchState(void);

    std::vector<std::pair<uint16_t, ScoreDTO >> getScores();
    GameScoreFeedback getMatchScores(void);

    void setZombie(uint32_t zombie_id, uint8_t zombie_type);
    void setThrowable(std::shared_ptr<Throwable> &&throwable);

    bool is_over(void);

    double calculate_mass_center();

    Match(const Match&) = delete;
    Match& operator=(const Match&) = delete;
};

#endif  // MATCH_H_
