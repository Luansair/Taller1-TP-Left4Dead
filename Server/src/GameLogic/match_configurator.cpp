#include "../../include/GameLogic/match_configurator.h"
#include "yaml-cpp/yaml.h"



MatchConfigurator::MatchConfigurator(void) {
}

void MatchConfigurator::configurate(uint8_t mode, uint8_t difficulty,
    std::map<uint32_t, std::shared_ptr<Zombie>> &zombies,
    std::map<uint32_t, std::shared_ptr<Soldier>> &soldiers,
    double dim_x, double dim_y, uint32_t *code_counter, uint16_t *zombie_counter, double mass_center) {

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

    amount_infected = config["infected"].as<int>();
    amount_spear = config["spear"].as<int>();
    amount_jumper = config["jumper"].as<int>();
    amount_venom = config["venom"].as<int>();
    amount_witch = config["witch"].as<int>(); 

    begin = *code_counter;
    int end = begin + amount_infected;
    for (int i = begin; i < end; i++) {
        std::shared_ptr<Zombie> zombie = factory.create(i, ZOMBIE);
        zombie->setRandomPosition(std::ref(soldiers), std::ref(zombies), dim_x, dim_y, mass_center);
        zombies.emplace(i, std::move(zombie));
        *zombie_counter += 1;
    }
    begin = end;
    end += amount_spear;
    for (int i = begin; i < end; i++) {
        std::shared_ptr<Zombie> zombie = factory.create(i, SPEAR);
        zombie->setRandomPosition(std::ref(soldiers), std::ref(zombies), dim_x, dim_y, mass_center);
        zombies.emplace(i, std::move(zombie));
        *zombie_counter += 1;
    }
    begin = end;
    end += amount_jumper;
    for (int i = begin; i < end; i++) {
        std::shared_ptr<Zombie> zombie = factory.create(i, JUMPER);
        zombie->setRandomPosition(std::ref(soldiers), std::ref(zombies), dim_x, dim_y, mass_center);
        zombies.emplace(i, std::move(zombie));
        *zombie_counter += 1;
    }
    begin = end;
    end += amount_venom;
    for (int i = begin; i < end; i++) {
        std::shared_ptr<Zombie> zombie = factory.create(i, VENOM);
        zombie->setRandomPosition(std::ref(soldiers), std::ref(zombies), dim_x, dim_y, mass_center);
        zombies.emplace(i, std::move(zombie));
        *zombie_counter += 1;
    }
    begin = end;
    end += amount_witch;
    for (int i = begin; i < end; i++) {
        std::shared_ptr<Zombie> zombie = factory.create(i, WITCH);
        zombie->setRandomPosition(std::ref(soldiers), std::ref(zombies), dim_x, dim_y, mass_center);
        zombies.emplace(i, std::move(zombie));
        *zombie_counter += 1;
    }
    *code_counter = end;
}

void MatchConfigurator::add_zombies(int amount,
    std::map<uint32_t, std::shared_ptr<Zombie>> &zombies,
    std::map<uint32_t, std::shared_ptr<Soldier>> &soldiers,
    double dim_x, double dim_y, uint32_t *code_counter, uint16_t *zombie_counter, double mass_center) {

    ZombieFactory factory;
    begin = *code_counter;
    uint32_t end = begin + amount;
    for (uint32_t i = begin; i < end; i++) {
        std::shared_ptr<Zombie> zombie = factory.create(i, ZOMBIE);
        zombie->setRandomPosition(std::ref(soldiers), std::ref(zombies), dim_x, dim_y, mass_center);
        zombies.emplace(i, std::move(zombie));
    }
    begin = end;
    end += amount;
    for (uint32_t i = begin; i < end; i++) {
        std::shared_ptr<Zombie> zombie = factory.create(i, SPEAR);
        zombie->setRandomPosition(std::ref(soldiers), std::ref(zombies), dim_x, dim_y, mass_center);
        zombies.emplace(i, std::move(zombie));
    }
    begin = end;
    end += amount;
    for (uint32_t i = begin; i < end; i++) {
        std::shared_ptr<Zombie> zombie = factory.create(i, JUMPER);
        zombie->setRandomPosition(std::ref(soldiers), std::ref(zombies), dim_x, dim_y, mass_center);
        zombies.emplace(i, std::move(zombie));
    }
    begin = end;
    end += amount;
    for (uint32_t i = begin; i < end; i++) {
        std::shared_ptr<Zombie> zombie = factory.create(i, VENOM);
        zombie->setRandomPosition(std::ref(soldiers), std::ref(zombies), dim_x, dim_y, mass_center);
        zombies.emplace(i, std::move(zombie));
    }
    begin = end;
    end += amount;
    for (uint32_t i = begin; i < end; i++) {
        std::shared_ptr<Zombie> zombie = factory.create(i, WITCH);
        zombie->setRandomPosition(std::ref(soldiers), std::ref(zombies), dim_x, dim_y, mass_center);
        zombies.emplace(i, std::move(zombie));
    }
    *code_counter = end;
    *zombie_counter += amount * 5;
}