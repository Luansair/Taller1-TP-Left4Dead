//
// Created by luan on 06/06/23.
//

#ifndef TP_DRAW_ACTOR_H
#define TP_DRAW_ACTOR_H

#include "../Animations/animation_manager.h"
#include "../../../Common/include/Information/state_dto_element.h"
#include "drawer_hpbar.h"

// La ventaja de tener SoldierOneDrawer con un action específico Drawer es
// cada action drawer puede guardar un estado distinto!
class ActorDrawer {
    AnimationManager& animation_manager;
    HealthBarDrawer hp_drawer;

    std::uint8_t type;
    std::uint8_t animation;
    std::uint8_t direction;
    std::uint16_t ammo;
    std::uint16_t actual_ammo;
    std::uint8_t timeleft;
    SDL2pp::Point sprite_destination;
    bool drawable;

    std::uint8_t sprite_index;
    unsigned int previous_frame_ticks;
public:

    explicit ActorDrawer(AnimationManager &animation_manager, SDL2pp::Renderer &renderer);
    // Necesito saber la cantidad de sprites para mandar un indice válido!
    // Primero hacer los calculos en update y guardar esa info.
    // Segundo hacer otro metodo draw que reciba una ref a HPBarDrawer
    void updateInfo(const ElementStateDTO &actor_state, std::int32_t window_x_pos, std::int32_t window_width,
                    std::int32_t window_height);
    void draw(std::uint32_t frame_ticks);
    void drawBar();
private:
    // void setActorType(uint8_t actor_type);
    // void setActorAnimation(uint8_t actor_action);
    void setActorDirection(int8_t actor_direction);
};


#endif //TP_DRAW_ACTOR_H
