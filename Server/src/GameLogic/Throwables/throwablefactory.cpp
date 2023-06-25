#include "../../../include/GameLogic/Throwables/throwablesfactory.h"
#include "../../../include/GameLogic/Throwables/throwable.h"
#include "../../../include/GameLogic/Throwables/smoke.h"
#include "../../../include/GameLogic/Throwables/grenade_t.h"
#include "../../../include/GameLogic/Throwables/poison.h"
#include "yaml-cpp/yaml.h"


ThrowableFactory::ThrowableFactory(uint32_t &code_counter) :
    code_counter(std::ref(code_counter)) {
}
std::shared_ptr<Throwable> ThrowableFactory::create(uint32_t *throwable_id, 
    uint8_t throwable_type, double x, double y, int8_t dir, 
    double dim_x, double dim_y, uint32_t thrower_id) {
    using YAML::LoadFile;
    using YAML::Node;

    Node node;
    double damage, scope, duration, speed;
    *throwable_id = code_counter;

    switch(throwable_type) {
        case SMOKE: {
            node = LoadFile(SERVER_CONFIG_PATH "/throwable.yaml")["smoke"];
            load_values(std::ref(node), &speed, &scope, &duration, &damage);
            return std::shared_ptr<Throwable> (new Smoke(code_counter++, x,
            y, speed, scope, duration, dir, dim_x, dim_y, thrower_id, damage));
        }
        case GRENADE: {
            node = LoadFile(SERVER_CONFIG_PATH "/throwable.yaml")["grenade"];
            load_values(std::ref(node), &speed, &scope, &duration, &damage);
            return std::shared_ptr<Throwable> (new Grenade_t(code_counter++, x,
            y, speed, scope, duration, dir, dim_x, dim_y, thrower_id, damage));
        }
        case POISON: {
            node = LoadFile(SERVER_CONFIG_PATH "/throwable.yaml")["poison"];
            load_values(std::ref(node), &speed, &scope, &duration, &damage);
            return std::shared_ptr<Throwable> (new Poison(code_counter++, x,
            y, speed, scope, duration, dir, dim_x, dim_y, thrower_id, damage));
        }
        case AERIAL: {
            node = LoadFile(SERVER_CONFIG_PATH "/throwable.yaml")["aerial"];
            load_values(std::ref(node), &speed, &scope, &duration, &damage);
            //return std::shared_ptr<Throwable> (new Aerial());
        }
    }
    return {nullptr};
}

void ThrowableFactory::load_values(const YAML::Node &node, double *speed, double *scope, double *duration, double *damage) {
    *speed = node["speed"].as<double>();
    *damage = node["damage"].as<double>();
    *scope = node["scope"].as<double>();
    *duration = node["duration"].as<double>();
}
