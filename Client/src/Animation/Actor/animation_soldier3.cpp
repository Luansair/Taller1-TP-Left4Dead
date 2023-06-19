#include "../../../include/Animations/Actor/animation_soldier3.h"
#include "../../../include/Animations/LoopType/looptype_no_loopable.h"
#include "../../../include/Animations/LoopType/looptype_loopable.h"

// Would like to choose the position to put the animation in the array.
SoldierThreeAnimation::SoldierThreeAnimation(SDL2pp::Renderer &renderer) :
    animations{
            ActionAnimation(renderer, RESOURCES_PATH "/Soldier_3/Attack.png",
                            loopable, 128, 128),
     ActionAnimation(renderer, RESOURCES_PATH "/Soldier_3/Dead.png",
                     no_loopable, 128, 128),
     ActionAnimation(renderer, RESOURCES_PATH "/Soldier_3/Grenade.png",
                     loopable, 128, 128),
     ActionAnimation(renderer, RESOURCES_PATH "/Soldier_3/Hurt.png",
                     loopable, 128, 128),
     ActionAnimation(renderer, RESOURCES_PATH "/Soldier_3/Idle.png",
                     loopable, 128, 128),
     ActionAnimation(renderer, RESOURCES_PATH "/Soldier_3/Recharge.png",
                     no_loopable, 128, 128),
     ActionAnimation(renderer, RESOURCES_PATH "/Soldier_3/Run.png",
                     loopable, 128, 128),
     ActionAnimation(renderer, RESOURCES_PATH "/Soldier_3/Shot_1.png",
                     loopable, 128, 128),
     ActionAnimation(renderer, RESOURCES_PATH "/Soldier_3/Shot_2.png",
                     loopable, 128, 128),
     ActionAnimation(renderer, RESOURCES_PATH "/Soldier_3/Smoke.png",
                     loopable, 128, 128),
     ActionAnimation(renderer, RESOURCES_PATH "/Soldier_3/Walk.png",
                     loopable, 128, 128)} {
}

void SoldierThreeAnimation::draw(std::uint8_t animation_index,
                               std::uint8_t *sprite_index,
                               std::uint8_t direction,
                               const SDL2pp::Rect &sprite_destination) {

    ActionAnimation& animation_to_draw = animations.at(animation_index);
    animation_to_draw.draw(sprite_index, direction, sprite_destination);
}