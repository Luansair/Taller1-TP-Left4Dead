#ifndef POSITION_H_
#define POSITION_H_

#include <utility>
#include <cstdint>
#include <map>
#include <memory>
#include <tuple>

class Position {
public:
    int16_t x;
    int16_t y;
    uint8_t width;
    uint8_t height;
    int16_t dim_x;
    int16_t dim_y;

    Position() {};

    explicit Position(int16_t x, int16_t y, uint8_t width, uint8_t height, int16_t dim_x, int16_t dim_y);

    bool collides(Position &other);

    int16_t getXPos(void) const;
    int16_t getYPos(void) const;
    uint8_t getWidth(void);
    uint8_t getHeight(void);
    void setXPos(int16_t new_x);
    void setYPos(int16_t new_y);

    std::tuple<int16_t, int16_t, bool> getXArea(void);
    std::tuple<int16_t, int16_t, bool> getYArea(void);

    bool operator==(const Position &other) const;

};

#endif  // POSITION_H_
