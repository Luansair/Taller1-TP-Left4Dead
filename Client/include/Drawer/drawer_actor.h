//
// Created by luan on 06/06/23.
//

#ifndef TP_DRAW_ACTOR_H
#define TP_DRAW_ACTOR_H

#include "../Animations/animation_manager.h"
#include "../../../Common/include/Information/state_dto_element.h"

// La ventaja de tener SoldierOneDrawer con un action específico Drawer es
// cada action drawer puede guardar un estado distinto!
class ActorDrawer {
    AnimationManager& animation_manager;
    std::uint8_t type;
    std::uint8_t animation;
    std::uint8_t direction;
    std::int32_t position_x;
    std::int32_t position_y;
    std::uint16_t health;
    std::uint16_t actual_health;
    SDL2pp::Point sprite_destination;

    std::uint8_t sprite_index;
    unsigned int previous_frame_ticks;

public:
    explicit ActorDrawer(AnimationManager& animation_manager);

    // Necesito saber la cantidad de sprites para mandar un indice válido!
    void updateInfo(const ElementStateDTO& actor_state);
    void draw(std::uint32_t frame_ticks, std::int32_t window_x_pos, std::int32_t window_width);

private:
    // void setActorType(uint8_t actor_type);
    // void setActorAnimation(uint8_t actor_action);
    void setActorDirection(int8_t actor_direction);
};


#endif //TP_DRAW_ACTOR_H
