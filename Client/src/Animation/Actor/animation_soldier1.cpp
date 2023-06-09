//
// Created by luan on 06/06/23.
//
#include "../../../include/Animations/Actor/animation_soldier1.h"
#include "../../../include/Animations/LoopType/looptype_no_loopable.h"
#include "../../../include/Animations/LoopType/looptype_loopable.h"

// Would like to choose the position to put the animation in the array.
SoldierOneAnimation::SoldierOneAnimation(SDL2pp::Renderer &renderer) :
    animations{
     ActionAnimation(renderer, RESOURCES_PATH "/Soldier_1/Attack.png",
                     loopable),
     ActionAnimation(renderer, RESOURCES_PATH "/Soldier_1/Dead.png",
                     no_loopable),
     ActionAnimation(renderer, RESOURCES_PATH "/Soldier_1/Explosion.png",
                     no_loopable),
     ActionAnimation(renderer, RESOURCES_PATH "/Soldier_1/Grenade.png",
                     loopable),
     ActionAnimation(renderer, RESOURCES_PATH "/Soldier_1/Hurt.png",
                     loopable),
     ActionAnimation(renderer, RESOURCES_PATH "/Soldier_1/Idle.png",
                     loopable),
     ActionAnimation(renderer, RESOURCES_PATH "/Soldier_1/Recharge.png",
                     no_loopable),
     ActionAnimation(renderer, RESOURCES_PATH "/Soldier_1/Run.png",
                     loopable),
     ActionAnimation(renderer, RESOURCES_PATH "/Soldier_1/Shot_1.png",
                     loopable),
     ActionAnimation(renderer, RESOURCES_PATH "/Soldier_1/Shot_2.png",
                     loopable),
     ActionAnimation(renderer, RESOURCES_PATH "/Soldier_1/Walk.png",
                     loopable)} {
}

void SoldierOneAnimation::draw(std::uint8_t animation_index,
                               std::uint8_t *sprite_index,
                               std::uint8_t direction,
                               const SDL2pp::Rect &sprite_destination) {

    ActionAnimation& animation_to_draw = animations.at(animation_index);
    animation_to_draw.draw(sprite_index, direction, sprite_destination);
}

