#include "../../include/Drawer/drawer_animation.h"
#include "../../../Common/include/Action/action_code.h"

AnimationDrawer::AnimationDrawer(SDL2pp::Renderer &renderer,
                                 const std::string &sprite_filepath) :
        renderer(renderer),
        texture(renderer, sprite_filepath),
        sprites() ,
        sprite_index(0),
        sprite_flip(SDL_FLIP_NONE),
        sprite_destination(0,0,128,128) {
    // Creates the rectangles that "cut" the desired sprite from the texture.
    // It assumes that each sprite is at the same distance and are equally
    // distributed throughout the entire image. It also assumes that the size
    // of each sprite is 128x128 pixels.
    // The sprite size can be parameters. Also padding can be a parameter.
    int sprite_width = 128;
    int sprite_height = 128;
    int texture_width = texture.GetWidth();

    for (int sprite = 0; sprite * sprite_width < texture_width; sprite++) {
        int sprite_x_position = sprite * sprite_width;
        sprites.emplace_back(sprite_x_position, 0, sprite_width, sprite_height);
    }
}

void AnimationDrawer::nextSprite() {
    if (sprite_index >= sprites.size() - 1) {
        reset();
    } else {
        sprite_index++;
    }

}

void AnimationDrawer::reset() {
    sprite_index = 0;
}

void AnimationDrawer::prevSprite() {
    if (sprite_index == 0) {
        sprite_index = sprites.size();
    } else {
        sprite_index--;
    }
}


void AnimationDrawer::draw(unsigned int frame_ticks) {
    renderer.Copy(texture, sprites[sprite_index], sprite_destination, 0.0,
                  SDL2pp::NullOpt, sprite_flip);
    sprite_index = (frame_ticks / 100) % sprites.size();
}

void AnimationDrawer::updateInfo(const DrawInfoDTO &draw_info) {
    sprite_destination.SetX(draw_info.position_x);
    sprite_destination.SetY(draw_info.position_y);
    if (draw_info.direction == DrawDirection::DRAW_RIGHT) {
        sprite_flip = SDL_FLIP_NONE;
    } else if (draw_info.direction == DrawDirection::DRAW_LEFT) {
        sprite_flip = draw_info.direction;
    } else {
        throw std::runtime_error("AnimationDrawer::updateInfo. Invalid "
                                 "direction\n");
    }
}

