//
// Created by luan on 06/06/23.
//
#ifndef TP_ANIMATION_ACTION_H
#define TP_ANIMATION_ACTION_H


#include <SDL2pp/SDL2pp.hh>

class ActionAnimation {
    SDL2pp::Renderer& renderer;
    SDL2pp::Texture texture;
    std::vector<SDL2pp::Rect> sprites;

    unsigned int frame_threshold;

public:
    ActionAnimation(SDL2pp::Renderer &renderer,
                    const std::string &texture_filepath,
                    unsigned int frame_threshold);

    void draw(unsigned int frame_ticks,
              std::uint8_t direction,
              const SDL2pp::Rect& sprite_destination);
};


#endif //TP_ANIMATION_ACTION_H
