#include "../../../include/GameLogic/Throwables/throwable.h"

Throwable::Throwable(uint32_t throwable_id, double x, double y, double speed, double scope, double duration, int8_t dir, double dim_x, double dim_y) :
    throwable_id(throwable_id),
    speed(speed),
    scope(scope),
    duration(duration),
    dir(dir),
    position(x, y, scope, scope, dim_x, dim_y) {}

void Throwable::activate(uint8_t state) {
    switch(state) {
    case ON:
        active = true;
        break;
    case OFF:
        active = false;
        break;
    }
}

void Throwable::simulateThrow(std::chrono::_V2::system_clock::time_point real_time, double dim_x, double dim_y) {
    std::chrono::duration<double> time = real_time - last_step_time;
    if (active) {
        std::chrono::duration<double> active_time = real_time - activation_time;
        if (active_time.count() >= duration) { 
            activate(OFF);  
            return; 
        }
    }
    if (!active) {activation_time = real_time; activate(ON);}
    double x_coord;
    if (dir == RIGHT) {
        x_coord = position.getXPos() + time.count() * speed;
        if (x_coord >= dim_x) { activate(OFF); return; }
    } else if (dir == LEFT) {
        x_coord = position.getXPos() - time.count() * speed;
        if (x_coord <= 0) { activate(OFF); return; }
    }
    Position new_position(x_coord, position.getYPos(), scope, scope, dim_x, dim_y);
    position = new_position;
    last_step_time = real_time;
}

bool Throwable::isInactive(void) {
    return !active;
}

uint32_t Throwable::getId(void) {
    return throwable_id;
}

int8_t Throwable::getDirX(void) {
    return dir;
}

Position& Throwable::getPosition(void) {
    return std::ref(position);
}