//
// Created by luan on 17/06/23.
//

#ifndef TP_CONFIG_GAME_H
#define TP_CONFIG_GAME_H

#include "yaml-cpp/yaml.h"

class GameConfig {
    YAML::Node config;

public:
    const std::uint16_t window_width;
    const std::uint16_t window_height;

    GameConfig();
};

#endif //TP_CONFIG_GAME_H
