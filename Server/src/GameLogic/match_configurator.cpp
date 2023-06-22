#include "../../include/GameLogic/match_configurator.h"
#include "yaml-cpp/yaml.h"
#define SOLDIERS_MAX 10
MatchConfigurator::MatchConfigurator(void) {
}

void MatchConfigurator::configurate(uint8_t mode, uint8_t difficulty,
    std::map<uint32_t, std::shared_ptr<Zombie>> &zombies,
    std::map<uint32_t, std::shared_ptr<Soldier>> &soldiers,
    double dim_x, double dim_y) {

    using YAML::LoadFile;
    using YAML::Node;
    Node config;
    ZombieFactory factory;

    switch (mode) {
    case SURVIVAL:
        switch (difficulty) {
        case DEASY:
            config = LoadFile(SERVER_CONFIG_PATH "/config.yaml")["survival_easy"];         
            break;
        case DNORMAL:
            config = LoadFile(SERVER_CONFIG_PATH "/config.yaml")["survival_normal"];         
            break;
        case DHARD:
            config = LoadFile(SERVER_CONFIG_PATH "/config.yaml")["survival_hard"];         
            break;
        case DINSANE:
            config = LoadFile(SERVER_CONFIG_PATH "/config.yaml")["survival_insane"];         
            break;
        }
        break;
    
    case CLEAR_THE_ZONE:
        switch (difficulty) {
        case DEASY:
            config = LoadFile(SERVER_CONFIG_PATH "/config.yaml")["clear_easy"];         
            break;
        case DNORMAL:
            config = LoadFile(SERVER_CONFIG_PATH "/config.yaml")["clear_normal"];         
            break;
        case DHARD:
            config = LoadFile(SERVER_CONFIG_PATH "/config.yaml")["clear_hard"];         
            break;
        case DINSANE:
            config = LoadFile(SERVER_CONFIG_PATH "/config.yaml")["clear_insane"];         
            break;
        }
        break;
    }

    const auto cant_infected =
        config["infected"].as<int>();
    const auto cant_spear =
        config["spear"].as<int>();
    const auto cant_jumper =
        config["jumper"].as<int>();
    const auto cant_venom =
        config["venom"].as<int>();
    const auto cant_witch =
        config["witch"].as<int>(); 

    int begin = SOLDIERS_MAX + 1;
    int end = begin + cant_infected;
    for (int i = begin; i < end; i++) {
        std::shared_ptr<Zombie> zombie = factory.create(i, ZOMBIE);
        zombie->setRandomPosition(std::ref(soldiers), std::ref(zombies), dim_x, dim_y);
        zombies.emplace(i, std::move(zombie));
    }
    begin = end;
    end += cant_spear;
    for (int i = begin; i < end; i++) {
        std::shared_ptr<Zombie> zombie = factory.create(i, SPEAR);
        zombie->setRandomPosition(std::ref(soldiers), std::ref(zombies), dim_x, dim_y);
        zombies.emplace(i, std::move(zombie));
    }
    begin = end;
    end += cant_jumper;
    for (int i = begin; i < end; i++) {
        std::shared_ptr<Zombie> zombie = factory.create(i, JUMPER);
        zombie->setRandomPosition(std::ref(soldiers), std::ref(zombies), dim_x, dim_y);
        zombies.emplace(i, std::move(zombie));
    }
    begin = end;
    end += cant_venom;
    for (int i = begin; i < end; i++) {
        std::shared_ptr<Zombie> zombie = factory.create(i, VENOM);
        zombie->setRandomPosition(std::ref(soldiers), std::ref(zombies), dim_x, dim_y);
        zombies.emplace(i, std::move(zombie));
    }
    begin = end;
    end += cant_witch;
    for (int i = begin; i < end; i++) {
        std::shared_ptr<Zombie> zombie = factory.create(i, WITCH);
        zombie->setRandomPosition(std::ref(soldiers), std::ref(zombies), dim_x, dim_y);
        zombies.emplace(i, std::move(zombie));
    }
}