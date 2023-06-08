//
// Created by luan on 06/06/23.
//
#ifndef TP_ANIMATION_MANAGER_H
#define TP_ANIMATION_MANAGER_H


#include <array>
#include <memory>
#include <SDL2pp/Rect.hh>
#include <SDL2pp/Renderer.hh>

#include "animation_actor.h"

class AnimationManager {
    std::array<std::unique_ptr<ActorAnimation>, 8> actors;

public:
    explicit AnimationManager(SDL2pp::Renderer& renderer);

    void draw(std::uint8_t actor_index,
              std::uint8_t animation_index,
              std::uint8_t *sprite_index,
              std::uint8_t direction,
              const SDL2pp::Rect& sprite_destination);
};

#endif //TP_ANIMATION_MANAGER_H
