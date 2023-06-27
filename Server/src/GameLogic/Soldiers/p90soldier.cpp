#include "../../../include/GameLogic/Soldiers/p90soldier.h"
#include "../../../include/GameLogic/Throwables/throwablesfactory.h"

P90Soldier::P90Soldier(
    uint32_t soldier_id,
    double width,
    double height,
    double speed,
    double health,
    std::unique_ptr<Weapon>&& weapon,
    double revive_radius,
    uint8_t t_type,
    double revive_cooldown,
    double reload_cooldown,
    double throw_cooldown,
    double throw_duration) :
    Soldier(soldier_id, width, height, speed, health, std::move(weapon), t_type, revive_radius, revive_cooldown, reload_cooldown, throw_cooldown, throw_duration) {
}


void P90Soldier::simulateThrow(std::chrono::_V2::system_clock::time_point real_time, double dim_x, double dim_y,
                            std::map<uint32_t, std::shared_ptr<Throwable>>& throwables, ThrowableFactory& factory) {
    if (throwed) {
        std::chrono::duration<double> time = real_time - throw_time;
        if (time.count() >= throw_duration) {
            last_throw_time = real_time; 
            start_throw(OFF);
            throwed = false;
            for(int i = dim_x / 10; i <= dim_x - 200;) {
                uint32_t id;
                std::shared_ptr<Throwable> grenade = factory.create(&id, t_type, position.getXPos() + i,
                position.getYPos() + i, dir_x, dim_x, dim_y, soldier_id);
                throwables.emplace(id, std::move(grenade));
                std::shared_ptr<Throwable> grenade2 = factory.create(&id, t_type, position.getXPos() - i,
                position.getYPos() - i, dir_x * -1, dim_x, dim_y, soldier_id);
                throwables.emplace(id, std::move(grenade2)); 
                i += dim_x / 10;
            }
            return;
        }
    } else {
        std::chrono::duration<double> time = real_time - last_throw_time;
        if (time.count() >= throw_cooldown) { 
            start_throw(ON);
            throwed = true;
            throw_time = real_time;
            return;
        }
        start_throw(OFF);
    }
}


uint8_t P90Soldier::getSoldierType(void) {
    return SOLDIER_P90;
}


// cambiar a soldier_2
uint8_t P90Soldier::getAction(void) {
    if (dying) return SOLDIER_2_DEAD;
    if (being_hurt) return SOLDIER_2_HURT;
    if (shooting) return SOLDIER_2_SHOOT_1;
    if (reloading) return SOLDIER_2_RECHARGE;
    if (moving) return SOLDIER_2_RUN;
    if (throwed) return SOLDIER_2_GRENADE;
    return SOLDIER_2_IDLE;
}
