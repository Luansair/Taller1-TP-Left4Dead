//
// Created by luan on 17/06/23.
//
#include "../include/config_game.h"

GameConfig::GameConfig() :
        config(YAML::LoadFile(CLIENT_CONFIG_PATH "/config.yaml")),
        window_width(config["window"]["width"].as<std::uint16_t>()),
        window_height(config["window"]["height"].as<std::uint16_t>()){
}

