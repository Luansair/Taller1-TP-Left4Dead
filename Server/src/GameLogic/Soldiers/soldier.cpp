#include "../../../include/GameLogic/Soldiers/soldier.h"
#include "../../../include/GameLogic/Zombies/zombie.h"
#include "../../../include/GameLogic/Throwables/throwablesfactory.h"
#include "../../../include/GameLogic/Throwables/throwable.h"
#include <random>
#include <tuple>
#define SPAWNRANGE 1000
#define LIVES 2

/* CONSTRUCTOR */

Soldier::Soldier(
    uint32_t soldier_id,
    double width,
    double height,
    double speed,
    double health,
    std::unique_ptr<Weapon>&& weapon,
    uint8_t t_type,
    double revive_radius,
    double revive_cooldown,
    double reload_cooldown,
    double throw_cooldown,
    double throw_duration) :
    soldier_id(soldier_id),
    speed(speed),
    health(health),
    width(width),
    height(height),
    position(0,0,width,height,0,0),
    weapon(std::move(weapon)),
    t_type(t_type),
    revive_radius(revive_radius),
    revive_cooldown(revive_cooldown),
    reload_cooldown(reload_cooldown),
    throw_cooldown(throw_cooldown),
    throw_duration(throw_duration) {
}

/* COMANDOS */

void Soldier::move(
    uint8_t state,
    uint8_t moveAxis,
    int8_t moveDirection,
    uint8_t moveForce) {
    
    if (dying) return; //esta linea es para que se quede totalmente quieto cuando está en el suelo.
    switch(state) {
        case ON:
            moving = true;
            reloading = shooting = throwing = reviving = being_hurt = throwed = false;
            axis = moveAxis;
            dir = moveDirection;
            if (moveAxis == X) dir_x = moveDirection;
            break;
        case OFF:
            moving = false;
            break;
    }
}

void Soldier::shoot(uint8_t state) {
    switch(state) {
        case ON:
            if (reloading) return;
            shooting = true;
            moving = reloading = throwing = reviving = being_hurt = throwed = false;
            break;
        case OFF:
            shooting = false;
            break;
    }
}

void Soldier::reload(uint8_t state) {
    switch(state) {
        case ON:
            if (!reloading) reload_time = std::chrono::system_clock::now();
            reloading = true;
            moving = shooting = throwing = reviving = being_hurt =  throwed = false;
            break;
        case OFF:
            reloading = false;
            break;
    }
}

void Soldier::throwGrenade(uint8_t state){
    switch(state) {
        case ON:
            if (throwed) {
                moving = false; return;
            }
            throwing = true;
            shooting = reloading = reviving = being_hurt = false;
            break;
        case OFF:
            throwing = false;
            break;
    }
}

void Soldier::recvDamage(uint8_t state, double damage) {
    switch(state) {
        case ON:
            reloading = throwing = reviving = throwed = false;
            being_hurt = true;
            damage_recv = damage;
            break;
        case OFF:
            being_hurt = false;
            break;
    }
}

void Soldier::start_dying(uint8_t state) {
    switch(state) {
        case ON:
            shooting = moving = throwing = being_hurt = reloading = reviving =  throwed = false;
            dying = true;
            break;
        case OFF:
            dying = false;
            times_revived += 1;
            break;
    }
}

void Soldier::revive(uint8_t state) {
    switch(state) {
        case ON:
            shooting = moving = throwing = reloading = being_hurt = throwed = false;
            reviving = true;
            break;
        case OFF:
            reviving = false;
            break;
    }
}

void Soldier::keep_reloading(uint8_t state) {
    switch(state) {
        case ON:
            shooting = moving = throwing = reviving = being_hurt = throwed = false;
            break;
        case OFF:
            break;
    }
}

void Soldier::idle(uint8_t state) {
    switch(state) {
        case ON:
            reloading = shooting = moving = throwing = reviving = being_hurt = throwed = false;
            break;
        case OFF:
            break;
    }
}

void Soldier::start_throw(uint8_t state) {
    switch(state) {
    case ON:
        throwing = true;
        reloading = shooting = moving = reviving = being_hurt = false;
        break;
    case OFF:
        throwing = false;
        break;
    }
}

void Soldier::change_grenade_type(uint8_t state) {
    switch(state) {
    case ON:
        changing = true;
        break;
    case OFF:
        changing = false;
        break;
    }
}

void Soldier::simulate_change_grenade(void) {
    if (t_type == GRENADE) { t_type = SMOKE; change_grenade_type(OFF); return; }
    if (t_type == SMOKE) { t_type = GRENADE; change_grenade_type(OFF); }
}


void Soldier::be_revived(void) {
    if (times_revived <= LIVES) {
        start_dying(OFF);
        actual_health = health * HALF;
        idle(ON);
        return;
    }
    alive = false;
}

void Soldier::increase_kill_counter(void) {
    kill_counter += 1;
}

/* SIMULADORES */

void Soldier::simulate(std::chrono::_V2::system_clock::time_point real_time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies, 
    std::map<uint32_t, std::shared_ptr<Throwable>>& throwables, double dim_x, double dim_y,
    ThrowableFactory& factory, double mass_center) {

    std::chrono::duration<double> time = real_time - last_step_time;

    if (dying) simulateDie(real_time, std::ref(soldiers));
    if (changing) simulate_change_grenade();
    if (reviving) simulateRevive(real_time, std::ref(soldiers));
    if (being_hurt) simulateRecvdmg(real_time);
    if (reloading) simulateReload(real_time);
    if (shooting) simulateShoot(real_time, time.count(), soldiers, zombies, dim_x);
    if (moving) simulateMove(time.count(), soldiers, zombies, dim_x, dim_y, mass_center);
    if (throwing) simulateThrow(real_time, dim_x, dim_y, throwables, std::ref(factory));
    last_step_time = real_time;
}

void Soldier::simulateRecvdmg(std::chrono::_V2::system_clock::time_point real_time) {
    if (damage_recv < actual_health) {
        actual_health -= damage_recv;
        recvDamage(OFF, 0);
        return;
    }
    // si muere, le seteo el tiempo de muerte y ejecuto el comando die.
    death_time = real_time;
    start_dying(ON);
}

void Soldier::simulateRevive(std::chrono::_V2::system_clock::time_point real_time,
std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers) {
    // verifico las colisiones. 
    RadialHitbox revive_zone(position.getXPos(), position.getYPos(), revive_radius);
    for (auto i = soldiers.begin(); i != soldiers.end(); i++) {
        Position other_pos = i->second->getPosition();
        if (i->second->getId() == soldier_id) continue;
        if (revive_zone.hits(other_pos)) {
            if (i->second->dying) {
                i->second->be_revived();
            }
        }
    }
}

void Soldier::simulateDie(std::chrono::_V2::system_clock::time_point real_time, std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers) {
    std::chrono::duration<double> time_dying = real_time - death_time;
    // si tiempo para revivirlo terminó, se muere.
    idle(ON);
    if (time_dying.count() > revive_cooldown) alive = false;
    bool everyone_is_dead =  true;
    for (auto i = soldiers.begin(); i != soldiers.end(); i++) {
        if (i->second->getId() == soldier_id) continue;
        if ((!i->second->isDead() && (!i->second->isDying()))) {
            everyone_is_dead = false;
        }
    }
    if (everyone_is_dead) alive = false;
}

void Soldier::simulateMove(
    double time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies, double dim_x, double dim_y, double mass_center) {
    // calculo proxima coordenada.
    std::tuple<double, double> next_coords = position.calculateNextPos(axis, dir, speed, time);
    if (abs(std::get<0>(next_coords)-mass_center) >= 600) return;
    Position next_pos(std::get<0>(next_coords), std::get<1>(next_coords), position.getWidth(), position.getHeight(), dim_x, dim_y);

    // verifico las colisiones.
    for (auto i = soldiers.begin(); i != soldiers.end(); i++) {
        Position other_pos = i->second->getPosition();
        if (i->second->getId() == soldier_id) continue;
        if (i->second->isDying() || i->second->isDead()) continue;
        if (next_pos.collides(other_pos)) {
            return;
        }
    }
    // lo mismo con los zombies
    for (auto i = zombies.begin(); i != zombies.end(); i++) {
        Position other_pos = i->second->getPosition();
        if (i->second->isDying() || i->second->isDead()) continue;
        if (next_pos.collides(other_pos)) {
            return;
        }
    }

    // si no colisiono cambio de pos
    position = next_pos;
}

void Soldier::simulateShoot(std::chrono::_V2::system_clock::time_point real_time, double time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies, double dim_x) {
    if (!(weapon->shoot(
        getPosition(), dir_x, dim_x, time, 
        std::ref(soldiers), std::ref(zombies)))) {
            reload(ON);
    }
}

void Soldier::simulateReload(std::chrono::_V2::system_clock::time_point real_time) {
    std::chrono::duration<double> time_reloading = real_time - reload_time;
    if (time_reloading.count() > reload_cooldown) {
        weapon->reload();
        reload(OFF);
    }
    keep_reloading(ON);
}

void Soldier::simulateThrow(std::chrono::_V2::system_clock::time_point real_time, double dim_x, double dim_y,
                            std::map<uint32_t, std::shared_ptr<Throwable>>& throwables, ThrowableFactory& factory) {
    if (throwed) {
        std::chrono::duration<double> time = real_time - throw_time;
        if (time.count() >= throw_duration) {
            last_throw_time = real_time; 
            start_throw(OFF);
            throwed = false;
            uint32_t id;
            std::shared_ptr<Throwable> grenade = factory.create(&id, t_type, position.getXPos() + dir_x * 10,
            position.getYPos(), dir_x, dim_x, dim_y, soldier_id);
            throwables.emplace(id, std::move(grenade)); 
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

/* GETTERS */

bool Soldier::isDead(void) {
    return (!alive);
}

bool Soldier::isDying(void) {
    return dying;
}

double Soldier::getWidth(void) {
    return width;
}
double Soldier::getHeight(void) {
    return height;
}

uint32_t Soldier::getId(void) {
    return soldier_id;
}

int8_t Soldier::getDir(void) {
    return dir;
}

int8_t Soldier::getDirX(void) {
    return dir_x;
}

double Soldier::getHealth(void) {
    return health;
}

double Soldier::getActualHealth(void) {
    return actual_health;
}

Position& Soldier::getPosition(void) {
    return std::ref(position);
}

const Position& Soldier::seePosition(void) const {
    return std::ref(position);
}

uint16_t Soldier::getKills(void) {
    return kill_counter;
}

double Soldier::secondsAlive(void) {
    std::chrono::duration<double> time_alive = last_step_time - born_time;
    return time_alive.count();
}

uint16_t Soldier::getAmmo(void) {
    return weapon->getAmmo();
}
    
uint16_t Soldier::getActualAmmo(void) {
    return weapon->getActualAmmo();
}

uint32_t Soldier::getBulletsFired() {
    return weapon->getBulletsFired();
}

double Soldier::getTimeLeft(void) {
    std::chrono::duration<double> time = last_step_time - throw_time;
    double left = throw_cooldown - time.count();
    if (left <= 0) return 0.0;
    return left;
}

uint8_t Soldier::isDeadFeedback(void) {
    if (!alive) return DEAD;
    return ALIVE;
}

/* SETTERS */

void Soldier::setPosition(Position&& new_pos) {
    position = new_pos;
}

void Soldier::setRandomPosition(
        const std::map<uint32_t, std::shared_ptr<Soldier>> &soldiers,
        const std::map<uint32_t, std::shared_ptr<Zombie>> &zombies, double dim_x, double dim_y) {
    using std::random_device;
    using std::mt19937;
    using std::uniform_int_distribution;
    using std::uint32_t;
    std::cout << dim_x << "-> centro de masa soldier \n";

    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int32_t> distx(dim_x- 500.0, dim_x + 500.0);
    uniform_int_distribution<int32_t> disty(0, dim_y);
    int32_t x_pos;
    int32_t y_pos;
    bool collides;
    do {
        collides = false;
        x_pos = distx(mt);
        std::cout << x_pos << "-> pos_random \n";
        y_pos = disty(mt);
        Position _position(x_pos, y_pos, getWidth(), getHeight(), dim_x, dim_y);
        for (const auto & soldier : soldiers) {
            Position other_pos = soldier.second->getPosition();
            if (_position.collides(other_pos)) {
                collides = true;
                break;
            }
        }
    } while (collides);
    Position _position(x_pos, y_pos, getWidth(), getHeight(), dim_x, dim_y);
    setPosition(std::move(_position));
}