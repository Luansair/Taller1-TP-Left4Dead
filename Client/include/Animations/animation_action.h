//
// Created by luan on 06/06/23.
//
#ifndef TP_ANIMATION_ACTION_H
#define TP_ANIMATION_ACTION_H


#include <SDL2pp/SDL2pp.hh>
#include "animation_loop_type.h"

class ActionAnimation {

    SDL2pp::Renderer& renderer;
    SDL2pp::Texture texture;
    std::vector<SDL2pp::Rect> sprites;
    std::unique_ptr<LoopType> loop_type;

    std::uint8_t determineFlipValue(std::uint8_t direction);

    void _draw(std::uint8_t sprite_index, std::uint8_t sprite_flip,
              const SDL2pp::Rect& sprite_destination);

public:
    ActionAnimation(SDL2pp::Renderer &renderer,
                    const std::string &texture_filepath,
                    LoopType* loop_type);

    void draw(std::uint8_t *sprite_index,
                      std::uint8_t direction,
                      const SDL2pp::Rect& sprite_destination);
};


#endif //TP_ANIMATION_ACTION_H
