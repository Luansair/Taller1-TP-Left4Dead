//
// Created by luan on 06/06/23.
//
#ifndef TP_ANIMATION_MANAGER_H
#define TP_ANIMATION_MANAGER_H


#include <array>
#include <memory>
#include <SDL2pp/Rect.hh>
#include <SDL2pp/Renderer.hh>

#include "Actor/animation_actor.h"
#include "Actor/animation_soldier1.h"
#include "Actor/animation_zombie.h"

class AnimationManager {
    SoldierOneAnimation soldier_1_animation;
    ZombieAnimation zombie_animation;
    // Other actor animations...

    std::array<ActorAnimation*, 8> actors;

public:
    explicit AnimationManager(SDL2pp::Renderer& renderer);

    void draw(std::uint8_t actor_index,
              std::uint8_t animation_index,
              std::uint8_t *sprite_index,
              std::uint8_t direction,
              const SDL2pp::Rect& sprite_destination);

    // Moving have a cost in performance due to array of arrays being moved.
    AnimationManager(AnimationManager&&) = delete;
    AnimationManager& operator=(const AnimationManager&&) = delete;

    AnimationManager(const AnimationManager&) = delete;
    AnimationManager& operator=(const AnimationManager&) = delete;
};

#endif //TP_ANIMATION_MANAGER_H