//
// Created by luan on 06/06/23.
//
#include <SDL2/SDL.h>
#include "../../include/Animations/animation_action.h"
#include "../../../Common/include/Information/information_code.h"

ActionAnimation::ActionAnimation(SDL2pp::Renderer &renderer,
                                 const std::string &texture_filepath,
                                 unsigned int frame_threshold) :
                                 renderer(renderer),
                                 texture(renderer,texture_filepath),
                                 sprites(),
                                 frame_threshold(frame_threshold) {
    int sprite_width = 128;
    int sprite_height = 128;
    int texture_width = texture.GetWidth();

    for (int sprite = 0; sprite * sprite_width < texture_width; sprite++) {
        int sprite_x_position = sprite * sprite_width;
        sprites.emplace_back(sprite_x_position, 0, sprite_width, sprite_height);
    }
}

void ActionAnimation::draw(unsigned int frame_ticks, std::uint8_t direction,
                           const SDL2pp::Rect &sprite_destination) {
    // Medio raro, es mejor si se le manda el index directamente. Sin embargo,
    // para sabe que index mandar hay que saber cuantos sprites hay!
    // Dado que texture es propiedad de este objeto, no hay forma de saberlo
    // desde fuera a menos que devuelva el size de alguna manera...
    std::uint8_t sprite_index =
            (frame_ticks / frame_threshold) % sprites.size();

    std::uint8_t sprite_flip;
    if (direction == DrawDirection::DRAW_RIGHT) {
        sprite_flip = SDL_FLIP_NONE;
    } else if (direction == DrawDirection::DRAW_LEFT) {
        sprite_flip = SDL_FLIP_HORIZONTAL;
    } else {
        throw std::runtime_error("ActionAnimation::draw. Invalid "
                                 "direction\n");
    }

    renderer.Copy(texture, sprites[sprite_index],
                  sprite_destination, 0.0,
                  SDL2pp::NullOpt, sprite_flip);
}

