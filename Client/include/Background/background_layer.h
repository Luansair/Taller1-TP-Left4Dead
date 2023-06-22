//
// Created by luan on 22/06/23.
//

#ifndef TP_BACKGROUND_LAYER_H
#define TP_BACKGROUND_LAYER_H

#include <SDL2pp/Texture.hh>
#include <SDL2pp/Renderer.hh>

class Layer {
    SDL2pp::Texture texture;
    SDL2pp::Renderer& renderer;

public:
    Layer(SDL2pp::Renderer& renderer, const std::string& layer_texture_filepath);

    void draw(const SDL2pp::Rect &destination);
    //void drawFillHorizontal(const SDL2pp::Point &position, std::int32_t width);

    Layer(Layer&&) = default;
    Layer& operator=(Layer&&) = delete;

    Layer(const Layer&) = delete;
    Layer& operator=(const Layer&) = delete;

    ~Layer() = default;
};

#endif //TP_BACKGROUND_LAYER_H
