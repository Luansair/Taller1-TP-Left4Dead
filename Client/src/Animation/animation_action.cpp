//
// Created by luan on 06/06/23.
//
#include <SDL2/SDL.h>
#include "../../include/Animations/animation_action.h"
#include "../../../Common/include/Information/information_code.h"

ActionAnimation::ActionAnimation(SDL2pp::Renderer &renderer,
                                 const std::string &texture_filepath,
                                 const LoopType& loop_type) :
        texture(renderer,texture_filepath),
        sprite_manager(texture, loop_type, renderer) {
}


//----------------------PUBLIC METHODS--------------------------------------//
void ActionAnimation::draw(std::uint8_t *sprite_index, std::uint8_t direction,
                           const SDL2pp::Rect &sprite_destination) {
    sprite_manager.draw(texture, sprite_index, direction, sprite_destination);
}



