//
// Created by luan on 17/06/23.
//
#include <SDL2/SDL.h>
#include "../include/handler_event.h"
#include "../../Common/include/Information/Actions/shoot_start.h"
#include "../../Common/include/Information/Actions/throw_start.h"
#include "../../Common/include/Information/Actions/moving_right_start.h"
#include "../../Common/include/Information/Actions/moving_left_start.h"
#include "../../Common/include/Information/Actions/moving_down_start.h"
#include "../../Common/include/Information/Actions/moving_up_start.h"
#include "../../Common/include/Information/Actions/shoot_stop.h"
#include "../../Common/include/Information/Actions/throw_stop.h"
#include "../../Common/include/Information/Actions/moving_right_stop.h"
#include "../../Common/include/Information/Actions/moving_left_stop.h"
#include "../../Common/include/Information/Actions/moving_down_stop.h"
#include "../../Common/include/Information/Actions/moving_up_stop.h"
#include "../../Common/include/Information/Actions/revive_start.h"
#include "../../Common/include/Information/Actions/revive_stop.h"

#define SEND_ACTION(action) actions_to_send.push(make_shared<action>())

EventHandler::EventHandler(
        Queue<std::shared_ptr<Information>> &actions_to_send,
        bool *quit) :
        actions_to_send(actions_to_send),
        quit(quit),
        event() ,
        keydown({nullptr}),
        keyup({nullptr}) {

    using std::make_shared;
    keydown.at(SDL_GetScancodeFromKey(SDLK_z)) = make_shared<StartShootAction>();
    keydown.at(SDL_GetScancodeFromKey(SDLK_c)) = make_shared<StartThrowAction>();
    keydown.at(SDL_GetScancodeFromKey(SDLK_x)) = make_shared<StartReviveAction>();
    keydown.at(SDL_GetScancodeFromKey(SDLK_RIGHT)) = make_shared<StartMovingRightAction>();
    keydown.at(SDL_GetScancodeFromKey(SDLK_LEFT)) = make_shared<StartMovingLeftAction>();
    keydown.at(SDL_GetScancodeFromKey(SDLK_UP)) = make_shared<StartMovingDownAction>();
    keydown.at(SDL_GetScancodeFromKey(SDLK_DOWN)) = make_shared<StartMovingUpAction>();

    keyup.at(SDL_GetScancodeFromKey(SDLK_z)) = make_shared<StopShootAction>();
    // keyup.at(SDL_GetScancodeFromKey(SDLK_c)) = make_shared<StopThrowAction>();
    keyup.at(SDL_GetScancodeFromKey(SDLK_x)) = make_shared<StopReviveAction>();
    keyup.at(SDL_GetScancodeFromKey(SDLK_RIGHT)) = make_shared<StopMovingRightAction>();
    keyup.at(SDL_GetScancodeFromKey(SDLK_LEFT)) = make_shared<StopMovingLeftAction>();
    keyup.at(SDL_GetScancodeFromKey(SDLK_UP)) = make_shared<StopMovingDownAction>();
    keyup.at(SDL_GetScancodeFromKey(SDLK_DOWN)) = make_shared<StopMovingUpAction>();

}

void EventHandler::start() {
    while (SDL_PollEvent(&event)) {
        processEvent();

        if (*quit)
            break;

    }
}

void EventHandler::processEvent() const {
    using std::shared_ptr;

    if (event.type == SDL_QUIT) {
        *quit = true;
    } else if (event.type == SDL_KEYDOWN) {

        if (event.key.keysym.sym == SDLK_ESCAPE) {
            *quit = true;
            return;
        }

        const shared_ptr<Information>& action_to_send =
                keydown.at(SDL_GetScancodeFromKey(event.key.keysym.sym));

        if (action_to_send != nullptr) {
            actions_to_send.push(action_to_send);
        }

    } else if (event.type == SDL_KEYUP) {

        const shared_ptr<Information>& action_to_send =
                keyup.at(SDL_GetScancodeFromKey(event.key.keysym.sym));

        if (action_to_send != nullptr) {
            actions_to_send.push(action_to_send);
        }

    }
}

/*
void EventHandler::processKeyDown() const {
    using std::make_shared;

    switch (event.key.keysym.sym)
    {
        case SDLK_ESCAPE:
            *quit = true;
            break;

        case SDLK_z:
            SEND_ACTION(StartShootAction);
            break;

        case SDLK_RIGHT:
            actions_to_send.push(
                    make_shared<StartMovingRightAction>());
            break;

        case SDLK_LEFT:
            actions_to_send.push(
                    make_shared<StartMovingLeftAction>());
            break;

        case SDLK_UP:
            actions_to_send.push(
                    make_shared<StartMovingDownAction>());
            break;

        case SDLK_DOWN:
            actions_to_send.push(
                    make_shared<StartMovingUpAction>());
            break;

        default:
            break;
    }
}


void EventHandler::processKeyUp() const{
    using std::make_shared;

    switch (event.key.keysym.sym)
    {
        case SDLK_z:
            actions_to_send.push(
                    make_shared<StopShootAction>());
            break;

        case SDLK_RIGHT:
            actions_to_send.push(
                    make_shared<StopMovingRightAction>());
            break;

        case SDLK_LEFT:
            actions_to_send.push(
                    make_shared<StopMovingLeftAction>());
            break;

        case SDLK_DOWN:
            actions_to_send.push(
                    make_shared<StopMovingUpAction>());
            break;

        case SDLK_UP:
            actions_to_send.push(
                    make_shared<StopMovingDownAction>());
            break;

        default:
            break;
    }
}
*/
