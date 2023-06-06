//
// Created by luan on 06/06/23.
//
#include "../../include/Animations/animation_soldier1.h"

// Would like to choose the position to put the animation in the array.
SoldierOneAnimation::SoldierOneAnimation(SDL2pp::Renderer &renderer) :
    animations{
    {ActionAnimation(renderer, RESOURCES_PATH "/Soldier_1/Attack.png", 100),
     ActionAnimation(renderer, RESOURCES_PATH "/Soldier_1/Dead.png", 100),
     ActionAnimation(renderer, RESOURCES_PATH "/Soldier_1/Explosion.png", 100),
     ActionAnimation(renderer, RESOURCES_PATH "/Soldier_1/Grenade.png", 100),
     ActionAnimation(renderer, RESOURCES_PATH "/Soldier_1/Hurt.png", 100),
     ActionAnimation(renderer, RESOURCES_PATH "/Soldier_1/Idle.png", 250),
     ActionAnimation(renderer, RESOURCES_PATH "/Soldier_1/Recharge.png", 100),
     ActionAnimation(renderer, RESOURCES_PATH "/Soldier_1/Run.png", 100),
     ActionAnimation(renderer, RESOURCES_PATH "/Soldier_1/Shot_1.png", 100),
     ActionAnimation(renderer, RESOURCES_PATH "/Soldier_1/Shot_2.png", 100),
     ActionAnimation(renderer, RESOURCES_PATH "/Soldier_1/Walk.png", 100)}} {
}

void SoldierOneAnimation::draw(std::uint8_t animation_index,
                               unsigned int frame_ticks,
                               std::uint8_t direction,
                               const SDL2pp::Rect &sprite_destination) {

    ActionAnimation& animation_to_draw = animations.at(animation_index);
    animation_to_draw.draw(frame_ticks, direction, sprite_destination);
}

