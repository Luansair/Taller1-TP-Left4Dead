#ifndef CLEARTHEZONE_H_
#define CLEARTHEZONE_H_

#include "match.h"

/* En “clear the zone” la cantidad de infectados en un escenario es fija y los jugadores ganan cuando
eliminan a todos ellos. */

class ClearTheZone : public Match {
public:
    explicit ClearTheZone(double x_dimension, double y_dimension, uint8_t difficulty);
    void configurate(uint8_t difficulty);

    void simulateStep(std::chrono::_V2::steady_clock::time_point real_time) override;
    void winMatch(void);
    void loseMatch(void);

};

#endif  // CLEARTHEZONE_H_
