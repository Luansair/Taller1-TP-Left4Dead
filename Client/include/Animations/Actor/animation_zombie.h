//
// Created by luan on 09/06/23.
//
#ifndef TP_ANIMATION_ZOMBIE_H
#define TP_ANIMATION_ZOMBIE_H

#include "../animation_action.h"
#include "animation_actor.h"

class ZombieAnimation : public ActorAnimation {
    std::array<ActionAnimation, 10> animations;

public:
    explicit ZombieAnimation(SDL2pp::Renderer& renderer);

    void draw(std::uint8_t animation_index,
              std::uint8_t *sprite_index,
              std::uint8_t direction,
              const SDL2pp::Rect& sprite_destination) override;

    // Should not move because it can affect performance!
    ZombieAnimation(ZombieAnimation&&) = delete;
    ZombieAnimation& operator=(ZombieAnimation&&) = delete;

    ZombieAnimation(const ZombieAnimation&) = delete;
    ZombieAnimation& operator=(const ZombieAnimation&) = delete;

    ~ZombieAnimation() override = default;
};
#endif //TP_ANIMATION_ZOMBIE_H
