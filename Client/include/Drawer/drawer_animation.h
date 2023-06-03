#ifndef TP_DRAWER_ANIMATION_H
#define TP_DRAWER_ANIMATION_H

#include <SDL2pp/SDL2pp.hh>
#include "draw_info_dto.h"

class AnimationDrawer {
    SDL2pp::Renderer& renderer;
    SDL2pp::Texture texture;
    std::vector<SDL2pp::Rect> sprites;
    std::uint8_t sprite_index;
    std::uint8_t sprite_flip;
    SDL2pp::Rect sprite_destination;

public:
    AnimationDrawer(SDL2pp::Renderer& renderer, const std::string &sprite_filepath);
    void nextSprite();
    void reset();
    void prevSprite();
    void updateInfo(const DrawInfoDTO& draw_info);
    void draw();
};

#endif // TP_DRAWER_ANIMATION_H
