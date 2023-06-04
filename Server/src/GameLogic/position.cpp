#include "../../include/GameLogic/position.h"

Position::Position(
    int16_t x,
    int16_t y,
    uint8_t width,
    uint8_t height) :
    x(x),
    y(y),
    width(width),
    height(height) {
}

bool Position::collides(Position &other) {
    int16_t x_other_max = other.getXMax();
    int16_t x_other_min = other.getXMin();
    int16_t y_other_max = other.getYMax();
    int16_t y_other_min = other.getYMin();
    int16_t x_max = getXMax();
    int16_t x_min = getXMin();
    int16_t y_max = getYMax();
    int16_t y_min = getYMin();

    if ((((x_other_min <= x_max) || (x_max <= x_other_max)) || (((x_other_min <= x_min) || (x_min <= x_other_max)))) && 
    (((y_other_min <= y_max) || (y_max <= y_other_max)) || (((y_other_min <= y_min) || (y_min <= y_other_max))))) return true;

    return false;
}

int16_t Position::getXPos(void) {
    return x;
}
int16_t Position::getYPos(void) {
    return y;
}

uint8_t Position::getWidth(void) {
    return width;
}

uint8_t Position::getHeight(void) {
    return height;
}

int16_t Position::getXMax(void) {
    return x + width * 0.5;
}

int16_t Position::getXMin(void) {
    return x - width * 0.5;
}

int16_t Position::getYMax(void) {
    return y + height * 0.5;
}

int16_t Position::getYMin(void) {
    return y - height * 0.5;
}

void Position::setXPos(int16_t new_x) {
    x = new_x;
}

void Position::setYPos(int16_t new_y) {
    y = new_y;
}
