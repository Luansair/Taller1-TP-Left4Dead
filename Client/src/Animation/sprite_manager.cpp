//
// Created by luan on 08/06/23.
//
#include <SDL.h>
#include "../../include/Animations/sprite_manager.h"
#include "../../../Common/include/Information/information_code.h"

SpriteManager::SpriteManager(const SDL2pp::Texture &texture,
                             const LoopType &loop_type,
                             SDL2pp::Renderer &renderer,
                             int sprite_width,
                             int sprite_height) :
    sprites(),
    loop_type(loop_type),
    renderer(renderer) {

    int texture_width = texture.GetWidth();

    for (int sprite = 0; sprite * sprite_width < texture_width; sprite++) {
        int sprite_x_position = sprite * sprite_width;
        sprites.emplace_back(sprite_x_position, 0, sprite_width,
                              sprite_height);
    }
}


//----------------------------PRIVATE METHODS------------------------------//
std::uint8_t SpriteManager::determineFlipValue(std::uint8_t direction) const {
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
void SpriteManager::_draw(SDL2pp::Texture &texture, std::uint8_t sprite_index,
                         std::uint8_t sprite_flip,
                         const SDL2pp::Rect &sprite_destination) {
    renderer.Copy(texture, sprites[sprite_index],
                  sprite_destination, 0.0,
                  SDL2pp::NullOpt, sprite_flip);
}


//----------------------PUBLIC METHODS--------------------------------------//

void SpriteManager::draw(SDL2pp::Texture &texture, std::uint8_t *sprite_index,
                         std::uint8_t direction,
                         const SDL2pp::Rect &sprite_destination) {
    loop_type.fixIndex(sprite_index, sprites.size() - 1);
    std::uint8_t sprite_flip = determineFlipValue(direction);
    _draw(texture, *sprite_index, sprite_flip, sprite_destination);
}
