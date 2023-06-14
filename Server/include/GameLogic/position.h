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

    ~Position() = default;

    explicit Position(int16_t x, int16_t y, uint8_t width, uint8_t height, int16_t dim_x, int16_t dim_y);

    [[nodiscard]] bool collides(const Position &other) const;

    [[nodiscard]] int16_t getXPos() const;
    [[nodiscard]] int16_t getYPos() const;
    [[nodiscard]] uint8_t getWidth() const;
    [[nodiscard]] uint8_t getHeight() const;
    void setXPos(int16_t new_x);
    void setYPos(int16_t new_y);

    [[nodiscard]] std::tuple<int16_t, int16_t, bool> getXArea() const;
    [[nodiscard]] std::tuple<int16_t, int16_t, bool> getYArea() const;

    bool operator==(const Position &other) const;

};

#endif  // POSITION_H_
