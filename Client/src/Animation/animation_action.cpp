//
// Created by luan on 06/06/23.
//
#include <SDL2/SDL.h>
#include "../../include/Animations/animation_action.h"
#include "../../../Common/include/Information/information_code.h"

ActionAnimation::ActionAnimation(SDL2pp::Renderer &renderer,
                                 const std::string &texture_filepath,
                                 LoopType* loop_type) :
        renderer(renderer),
        texture(renderer,texture_filepath),
        sprites() ,
        loop_type(loop_type) {
    int sprite_width = 128;
    int sprite_height = 128;
    int texture_width = texture.GetWidth();

    for (int sprite = 0; sprite * sprite_width < texture_width; sprite++) {
        int sprite_x_position = sprite * sprite_width;
        sprites.emplace_back(sprite_x_position, 0, sprite_width, sprite_height);
    }
}

std::uint8_t ActionAnimation::determineFlipValue(std::uint8_t direction) {
    std::uint8_t sprite_flip;
    if (direction == DrawDirection::DRAW_RIGHT) {
        sprite_flip = SDL_FLIP_NONE;
    } else if (direction == DrawDirection::DRAW_LEFT) {
        sprite_flip = SDL_FLIP_HORIZONTAL;
    } else {
        throw std::runtime_error("ActionAnimation::draw. Invalid "
                                 "direction\n");
    }
    return sprite_flip;
}

void ActionAnimation::_draw(std::uint8_t sprite_index, std::uint8_t sprite_flip,
                           const SDL2pp::Rect &sprite_destination) {
    renderer.Copy(texture, sprites[sprite_index],
                  sprite_destination, 0.0,
                  SDL2pp::NullOpt, sprite_flip);
}

void ActionAnimation::draw(std::uint8_t *sprite_index, std::uint8_t direction,
                           const SDL2pp::Rect &sprite_destination) {
    loop_type->fixIndex(sprite_index, sprites.size() - 1);
    std::uint8_t sprite_flip = determineFlipValue(direction);
    _draw(*sprite_index, sprite_flip, sprite_destination);
}



