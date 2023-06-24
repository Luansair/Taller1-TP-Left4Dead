//
// Created by luan & pedro on 06/06/23.
//
#ifndef TP_ANIMATION_MANAGER_H
#define TP_ANIMATION_MANAGER_H


#include <array>
#include <memory>
#include <SDL2pp/Rect.hh>
#include <SDL2pp/Renderer.hh>

#include "Actor/animation_actor.h"
#include "Actor/animation_soldier1.h"
#include "Actor/animation_soldier2.h"
#include "Actor/animation_soldier3.h"
#include "Actor/animation_zombie.h"
#include "Actor/animation_witch.h"
#include "Actor/animation_spear.h"
#include "Actor/animation_jumper.h"
#include "Actor/animation_venom.h"

class AnimationManager {
    SoldierOneAnimation soldier_1_animation;
    SoldierTwoAnimation soldier_2_animation;
    SoldierThreeAnimation soldier_3_animation;
    ZombieAnimation zombie_animation;
    WitchAnimation witch_animation;
    SpearAnimation spear_animation;
    JumperAnimation jumper_animation;
    VenomAnimation venom_animation;
    // Other actor animations...

    std::array<ActorAnimation*, 8> actors;

public:
    explicit AnimationManager(SDL2pp::Renderer& renderer);

    void
    draw(std::uint8_t actor_index, std::uint8_t animation_index, std::uint8_t *sprite_index, std::uint8_t direction,
         const SDL2pp::Point &sprite_destination, std::uint32_t frame_ticks);

    // Moving have a cost in performance due to array of arrays being moved.
    AnimationManager(AnimationManager&&) = delete;
    AnimationManager& operator=(const AnimationManager&&) = delete;

    AnimationManager(const AnimationManager&) = delete;
    AnimationManager& operator=(const AnimationManager&) = delete;
};

#endif //TP_ANIMATION_MANAGER_H
