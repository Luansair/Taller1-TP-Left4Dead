//
// Created by luan on 06/06/23.
//
#include "../../include/Animations/animation_manager.h"
#include "../../include/Animations/animation_soldier1.h"
#include "../../../Common/include/Information/information_code.h"

AnimationManager::AnimationManager(SDL2pp::Renderer& renderer) :
    actors{
            {nullptr,
             nullptr,
             nullptr,
             nullptr,
             nullptr,
             nullptr,
             nullptr,
             nullptr}
    }
    {
        actors.at(ElementType::SOLDIER_1) = std::unique_ptr<ActorAnimation>(
                        new SoldierOneAnimation(renderer));
    }

void
AnimationManager::draw(std::uint8_t actor_index, std::uint8_t animation_index,
                       std::uint8_t *sprite_index, std::uint8_t direction,
                       const SDL2pp::Rect &sprite_destination) {
    ActorAnimation* actor_animation = actors.at(actor_index).get();

    if (actor_animation == nullptr) {
        throw std::runtime_error("AnimationManager::draw. Invalid Actor Type"
                                 ".\n");
    }

    actor_animation->draw(animation_index, sprite_index, direction,
                          sprite_destination);
}

