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
                            loopable, 128, 128, 100),
            ActionAnimation(renderer, RESOURCES_PATH "/Soldier_1/Dead.png",
                            no_loopable, 128, 128, 100),
            ActionAnimation(renderer, RESOURCES_PATH "/Soldier_1/Explosion.png",
                            no_loopable, 128, 128, 150),
            ActionAnimation(renderer, RESOURCES_PATH "/Soldier_1/Grenade.png",
                            loopable, 128, 128, 100),
            ActionAnimation(renderer, RESOURCES_PATH "/Soldier_1/Hurt.png",
                            loopable, 128, 128, 80),
            ActionAnimation(renderer, RESOURCES_PATH "/Soldier_1/Idle.png",
                            loopable, 128, 128, 200),
            ActionAnimation(renderer, RESOURCES_PATH "/Soldier_1/Recharge.png",
                            no_loopable, 128, 128, 100),
            ActionAnimation(renderer, RESOURCES_PATH "/Soldier_1/Run.png",
                            loopable, 128, 128, 100),
            ActionAnimation(renderer, RESOURCES_PATH "/Soldier_1/Shot_1.png",
                            loopable, 128, 128, 100),
            ActionAnimation(renderer, RESOURCES_PATH "/Soldier_1/Shot_2.png",
                            loopable, 128, 128, 100),
            ActionAnimation(renderer, RESOURCES_PATH "/Soldier_1/Walk.png",
                            loopable, 128, 128, 100)} {
}

void SoldierOneAnimation::draw(std::uint8_t animation_index, std::uint8_t *sprite_index, std::uint8_t direction,
                               const SDL2pp::Point &sprite_destination, std::uint32_t frame_ticks) {

    ActionAnimation& animation_to_draw = animations.at(animation_index);
    animation_to_draw.draw(sprite_index, direction, sprite_destination, frame_ticks);
}

