//
// Created by luan on 22/06/23.
//
#include "../../include/Background/background_war1.h"

War1Background::War1Background(SDL2pp::Renderer &renderer) :
        layers {
                Layer(renderer, RESOURCES_PATH "/backgrounds/War1/Bright/fence.png"),
                Layer(renderer, RESOURCES_PATH "/backgrounds/War1/Bright/houses1.png"),
                Layer(renderer, RESOURCES_PATH "/backgrounds/War1/Bright/houses2.png"),
                Layer(renderer, RESOURCES_PATH "/backgrounds/War1/Bright/house3.png"),
                Layer(renderer, RESOURCES_PATH "/backgrounds/War1/Bright/road.png"),
                Layer(renderer, RESOURCES_PATH "/backgrounds/War1/Bright/ruins.png"),
                Layer(renderer, RESOURCES_PATH "/backgrounds/War1/Bright/sky.png"),
                Layer(renderer, RESOURCES_PATH "/backgrounds/War1/Bright/sun.png")
        }{
}

void War1Background::draw(std::uint8_t layer_type, const SDL2pp::Rect &destination) {
    layers.at(layer_type).draw(destination);
}

