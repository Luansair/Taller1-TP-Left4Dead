//
// Created by luan on 06/06/23.
//
#include "../../include/Drawer/drawer_actor.h"
#include "../../include/Animations/animation_code.h"
#include "../../../Common/include/Information/information_code.h"

ActorDrawer::ActorDrawer(AnimationManager &animation_manager) :
        animation_manager(animation_manager),
        type(SOLDIER_1),
        animation(SOLDIER_1_IDLE),
        direction(DRAW_RIGHT),
        sprite_destination(0,0,128,128),
        sprite_index(0),
        previous_frame_ticks(0) {

}

// Paso sprite_index como puntero y si supera el tamaño me lo hace 0.
// Para que todos los jugadores vean las mismas animaciones, el server deberá
// enviar la animación específica, incluso si hay 3 tipos de ataques.
// Por ende la informacion de vuelta no es la misma que la de ida.
void ActorDrawer::updateInfo(const ElementStateDTO &actor_state) {
    if (this->animation != actor_state.action) {
        sprite_index = 0;
    }
    // se congela la animación, si le mando directamente desde server sin traducir anda bien.
    setActorType(actor_state.type);
    //this->animation = actor_state.action;
    setActorAnimation(actor_state.action);
    setActorDirection(actor_state.direction);
    sprite_destination.SetX(actor_state.position_x);
    sprite_destination.SetY(actor_state.position_y);
}

void ActorDrawer::draw(unsigned int frame_ticks) {
    if (frame_ticks - previous_frame_ticks > 100) {
        sprite_index += 1;
        previous_frame_ticks = frame_ticks;
    }
    animation_manager.draw(type, animation, &sprite_index, direction,
                           sprite_destination);
}

void ActorDrawer::setActorType(uint8_t actor_type) {
    switch (actor_type)
    {
    case 0:
        this->type = SOLDIER_1;
        break;
    
    case 1:
        this->type = SOLDIER_2;
        break;

    case 2:
        this->type = SOLDIER_3;
        break;

    case 3:
        this->type = ZOMBIE;
        break;
    }
}

void ActorDrawer::setActorAnimation(uint8_t actor_action) {
    switch (actor_action)
    {
    case ACTION_MOVE:
        this->animation = SOLDIER_1_RUN;
        break;
    
    case ACTION_RELOAD:
        this->animation = SOLDIER_1_RECHARGE;
        break;

    case ACTION_SHOOT:
        this->animation = SOLDIER_1_SHOOT_1;
        break;

    case ACTION_IDLE:
        this->animation = SOLDIER_1_IDLE;
        break;
    }
}

void ActorDrawer::setActorDirection(int8_t actor_direction) {
    switch (actor_direction)
    {
    case RIGHT:
        this->direction = DRAW_RIGHT;
        break;
    
    case LEFT:
        this->direction = DRAW_LEFT;
        break;
    }
}
