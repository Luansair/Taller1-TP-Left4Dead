//
// Created by luan on 17/06/23.
//
#include <SDL2/SDL.h>
#include "../include/handler_event.h"
#include "../../Common/include/Information/Actions/shoot_start.h"
#include "../../Common/include/Information/Actions/moving_right_start.h"
#include "../../Common/include/Information/Actions/moving_left_start.h"
#include "../../Common/include/Information/Actions/moving_down_start.h"
#include "../../Common/include/Information/Actions/moving_up_start.h"
#include "../../Common/include/Information/Actions/shoot_stop.h"
#include "../../Common/include/Information/Actions/moving_right_stop.h"
#include "../../Common/include/Information/Actions/moving_left_stop.h"
#include "../../Common/include/Information/Actions/moving_down_stop.h"

EventHandler::EventHandler(
        Queue<std::shared_ptr<Information>> &actions_to_send,
        bool *quit) :
        actions_to_send(actions_to_send),
        quit(quit),
        event() {
}

void EventHandler::start() {
    while (*quit && SDL_PollEvent(&event)) {
        processEvent();
    }
}

void EventHandler::processEvent() const {
    if (event.type == SDL_QUIT) {
        *quit = true;
    } else if (event.type == SDL_KEYDOWN) {
        processKeyDown();
    } else if (event.type == SDL_KEYUP) {
        processKeyUp();
    }
}

void EventHandler::processKeyDown() const {
    using std::make_shared;

    switch (event.key.keysym.sym)
    {
        case SDLK_ESCAPE:
            *quit = true;
            break;

        case SDLK_z:
            actions_to_send.push(
                    make_shared<StartShootAction>());
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
                    make_shared<StartMovingUpAction>());
            break;

        case SDLK_UP:
            actions_to_send.push(
                    make_shared<StopMovingDownAction>());
            break;

        default:
            break;
    }
}

