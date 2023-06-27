//
// Created by luan on 06/06/23.
//
#include <SDL2/SDL.h>
#include "../../include/Animations/animation_action.h"
#include "../../../Common/include/Information/information_code.h"

ActionAnimation::ActionAnimation(SDL2pp::Renderer &renderer, const std::string &texture_filepath,
                                 const LoopType &loop_type, int sprite_width, int sprite_height,
                                 std::uint32_t ms_to_change_sprite) :
        texture(renderer,texture_filepath),
        sprite_manager(texture, loop_type, renderer, sprite_width, sprite_height, ms_to_change_sprite) {
}


//----------------------PUBLIC METHODS--------------------------------------//
void ActionAnimation::draw(std::uint8_t *sprite_index, std::uint8_t direction, const SDL2pp::Point &sprite_destination,
                           std::uint32_t frame_ticks) {
    sprite_manager.draw(texture, sprite_index, direction, sprite_destination, frame_ticks);
}



