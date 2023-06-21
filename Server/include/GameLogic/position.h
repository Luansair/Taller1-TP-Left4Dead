#ifndef POSITION_H_
#define POSITION_H_

#include "../../../Common/include/Information/information_code.h"

#include <utility>
#include <cstdint>
#include <map>
#include <memory>
#include <tuple>

class Position {
public:
    double x;
    double y;
    double width;
    double height;
    double dim_x;
    double dim_y;

    ~Position() = default;

    explicit Position(double x, double y, double width, double height, double dim_x, double dim_y);

    [[nodiscard]] bool collides(const Position &other) const;

    [[nodiscard]] double getXPos() const;
    [[nodiscard]] double getYPos() const;
    [[nodiscard]] double getWidth() const;
    [[nodiscard]] double getHeight() const;
    std::tuple<double, double> calculateNextPos(uint8_t axis, int8_t dir, double speed, double time);
    void setXPos(double new_x);
    void setYPos(double new_y);

    [[nodiscard]] std::tuple<double, double, bool> getXArea() const;
    [[nodiscard]] std::tuple<double, double, bool> getYArea() const;

    bool operator==(const Position &other) const;

};

#endif  // POSITION_H_
