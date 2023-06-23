//
// Created by luan on 22/06/23.
//
#include "../../include/Background/background_manager.h"

BackgroundManager::BackgroundManager(SDL2pp::Renderer &renderer) :
        war1_background(renderer),
        backgrounds() {
    backgrounds.at(BACKGROUND_WAR1) = &war1_background;
    // backgrounds.at(BACKGROUND_WAR2) = &war2_background;
    // backgrounds.at(BACKGROUND_WAR3) = &war3_background;
    // backgrounds.at(BACKGROUND_WAR4) = &war4_background;
}

void
BackgroundManager::drawLayer(std::uint8_t background_type, std::uint8_t layer_type, const SDL2pp::Rect &destination) {
    backgrounds.at(background_type)->draw(layer_type, destination);
}

