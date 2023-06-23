#include "../../../include/GameLogic/Throwables/poison.h"

Poison::Poison(uint32_t throwable_id, double x, double y, double speed, double scope, double duration, int8_t dir, double dim_x, double dim_y) :
    Throwable(throwable_id, x, y, speed, scope, duration, dir, dim_x, dim_y) {}

uint8_t Poison::getThrowerType() {
    return VENOM;
}

uint8_t Poison::getAction() {
    return VENOM_ATTACK_1A;
}