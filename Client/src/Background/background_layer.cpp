//
// Created by luan on 22/06/23.
//
#include "../../include/Background/background_layer.h"

Layer::Layer(SDL2pp::Renderer &renderer, const std::string &layer_texture_filepath) :
        texture(renderer, layer_texture_filepath),
        renderer(renderer) {
}

void Layer::draw(const SDL2pp::Rect &destination) {
    renderer.Copy(texture, SDL2pp::NullOpt, destination);
}

