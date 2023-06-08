//
// Created by luan on 06/06/23.
//
#include "../../include/Animations/animation_soldier1.h"
#include "../../include/Animations/animation_no_loopable.h"
#include "../../include/Animations/animation_loopable.h"

// Would like to choose the position to put the animation in the array.
SoldierOneAnimation::SoldierOneAnimation(SDL2pp::Renderer &renderer) :
    animations{
    {ActionAnimation(renderer, RESOURCES_PATH "/Soldier_1/Attack.png",
                     new Loopable()),
     ActionAnimation(renderer, RESOURCES_PATH "/Soldier_1/Dead.png",
                     new NoLoopable()),
     ActionAnimation(renderer, RESOURCES_PATH "/Soldier_1/Explosion.png",
                     new NoLoopable()),
     ActionAnimation(renderer, RESOURCES_PATH "/Soldier_1/Grenade.png",
                     new Loopable()),
     ActionAnimation(renderer, RESOURCES_PATH "/Soldier_1/Hurt.png",
                     new Loopable()),
     ActionAnimation(renderer, RESOURCES_PATH "/Soldier_1/Idle.png",
                     new Loopable()),
     ActionAnimation(renderer, RESOURCES_PATH "/Soldier_1/Recharge.png",
                     new NoLoopable()),
     ActionAnimation(renderer, RESOURCES_PATH "/Soldier_1/Run.png",
                     new Loopable()),
     ActionAnimation(renderer, RESOURCES_PATH "/Soldier_1/Shot_1.png",
                     new Loopable()),
     ActionAnimation(renderer, RESOURCES_PATH "/Soldier_1/Shot_2.png",
                     new Loopable()),
     ActionAnimation(renderer, RESOURCES_PATH "/Soldier_1/Walk.png",
                     new Loopable())}} {
}

void SoldierOneAnimation::draw(std::uint8_t animation_index,
                               std::uint8_t *sprite_index,
                               std::uint8_t direction,
                               const SDL2pp::Rect &sprite_destination) {

    ActionAnimation& animation_to_draw = animations.at(animation_index);
    animation_to_draw.draw(sprite_index, direction, sprite_destination);
}

