#ifndef POSITION_H_
#define POSITION_H_

#include <utility>
#include <cstdint>
#include <map>
#include <memory>

class Position {
public:
    int16_t x;
    int16_t y;
    uint8_t width;
    uint8_t height;

    Position() {};

    explicit Position(int16_t x, int16_t y, uint8_t width, uint8_t height);

    bool collides(Position &other);

    int16_t getXPos(void);
    int16_t getYPos(void);
    uint8_t getWidth(void);
    uint8_t getHeight(void);

    int16_t getXMax(void);
    int16_t getXMin(void);
    int16_t getYMax(void);
    int16_t getYMin(void);
    void setXPos(int16_t new_x);
    void setYPos(int16_t new_y);


};

#endif  // POSITION_H_
