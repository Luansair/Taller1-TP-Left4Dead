//
// Created by luan on 22/06/23.
//

#ifndef TP_BACKGROUND_LAYER_H
#define TP_BACKGROUND_LAYER_H

#include <SDL2pp/Texture.hh>

class Layer {
    SDL2pp::Texture texture;

public:
    Layer(SDL2pp::Renderer& renderer, const std::string& layer_texture_filepath);

    void draw(const SDL2pp::Point &position);

    Layer(Layer&&) = default;
    Layer& operator=(Layer&&) = default;

    Layer(const Layer&) = delete;
    Layer& operator=(const Layer&) = delete;

    ~Layer() = default;
};

#endif //TP_BACKGROUND_LAYER_H
