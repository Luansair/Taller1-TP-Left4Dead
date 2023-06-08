//
// Created by luan on 06/06/23.
//

#ifndef TP_ANIMATION_ACTOR_H
#define TP_ANIMATION_ACTOR_H

#include <SDL2pp/Renderer.hh>

class ActorAnimation {

public:
    ActorAnimation() = default;

    virtual void draw(std::uint8_t animation_index,
                      std::uint8_t *sprite_index,
                      std::uint8_t direction,
                      const SDL2pp::Rect& sprite_destination) = 0;

    ActorAnimation(ActorAnimation&&) = delete;
    ActorAnimation(const ActorAnimation&) = delete;

    virtual ~ActorAnimation() = default;
};


#endif //TP_ANIMATION_ACTOR_H
