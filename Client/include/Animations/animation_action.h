//
// Created by luan on 06/06/23.
//
#ifndef TP_ANIMATION_ACTION_H
#define TP_ANIMATION_ACTION_H


#include <SDL2pp/SDL2pp.hh>
#include "LoopType/looptype.h"
#include "sprite_manager.h"

class ActionAnimation {

    SDL2pp::Texture texture;
    SpriteManager sprite_manager;

public:
    ActionAnimation(SDL2pp::Renderer &renderer,
                    const std::string &texture_filepath,
                    const LoopType &loop_type, int sprite_width,
                    int sprite_height);

    void draw(std::uint8_t *sprite_index,
              std::uint8_t direction,
              const SDL2pp::Point &sprite_destination);

    ActionAnimation(ActionAnimation&&) = default;
    ActionAnimation& operator=(ActionAnimation&&) = delete;

    ActionAnimation(const ActionAnimation&) = delete;
    ActionAnimation& operator=(const ActionAnimation&) = delete;

    ~ActionAnimation() = default;
};


#endif //TP_ANIMATION_ACTION_H
