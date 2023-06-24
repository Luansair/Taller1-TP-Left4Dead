//
// Created by luan on 08/06/23.
//

#ifndef TP_SPRITE_MANAGER_H
#define TP_SPRITE_MANAGER_H

#include <vector>
#include <SDL2pp/Rect.hh>
#include <SDL2pp/Texture.hh>
#include "LoopType/looptype.h"
#include "SDL2pp/Renderer.hh"

class SpriteManager {
    std::vector<SDL2pp::Rect> sprites;
    const LoopType& loop_type;
    SDL2pp::Renderer& renderer;
    std::uint32_t ms_to_change;

    [[nodiscard]] std::uint8_t determineFlipValue(std::uint8_t direction) const;

    void _draw(SDL2pp::Texture& texture,
               std::uint8_t sprite_index, std::uint8_t sprite_flip,
               const SDL2pp::Point &sprite_destination);
public:
    SpriteManager(const SDL2pp::Texture &texture, const LoopType &loop_type, SDL2pp::Renderer &renderer,
                  int sprite_width, int sprite_height, std::uint32_t ms_to_change);

    void draw(SDL2pp::Texture &texture, std::uint8_t *sprite_index, std::uint8_t direction,
              const SDL2pp::Point &sprite_destination, std::uint32_t frame_ticks);

    SpriteManager(SpriteManager&&) = default;
    SpriteManager& operator=(SpriteManager&&) = delete;

    SpriteManager(const SpriteManager&) = delete;
    SpriteManager& operator=(const SpriteManager&) = delete;

    ~SpriteManager() = default;
};
#endif //TP_SPRITE_MANAGER_H
