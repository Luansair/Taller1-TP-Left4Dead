#ifndef SURVIVAL_H_
#define SURVIVAL_H_

#include "match.h"

/* En el modo “survival”, a medida que pasa el tiempo aparecen más y más infectados y estos se van
haciendo progresivamente más fuertes, resistentes y veloces.
No hay condición de victoria: la muerte es inevitable y solo se compite por ver quién resiste más tiempo.
Al finalizar una partida se computa la cantidad de infectados eliminados, la cantidad de balas disparadas y el
tiempo de la partida.
En el modo “survival” estas estadísticas se guardan en el servidor y muestran a los jugadores en que
ranking han quedado (hay 3 rankings, uno por cada una de las estadísticas). */

class Survival : public Match {
public:
    explicit Survival(double x_dimension, double y_dimension, uint8_t difficulty);
    void configurate(uint8_t difficulty);

    void simulateStep(std::chrono::_V2::steady_clock::time_point real_time) override;
    void loseMatch(void);

};

#endif  // SURVIVAL_H_
