//
// Created by luan on 17/06/23.
//
#include <SDL2/SDL.h>
#include "../include/handler_event.h"
#include "../../Common/include/Information/Actions/shoot_start.h"
#include "../../Common/include/Information/Actions/exit_start.h"
#include "../../Common/include/Information/Actions/reload_start.h"
#include "../../Common/include/Information/Actions/throw_start.h"
#include "../../Common/include/Information/Actions/change_start.h"
#include "../../Common/include/Information/Actions/moving_right_start.h"
#include "../../Common/include/Information/Actions/moving_left_start.h"
#include "../../Common/include/Information/Actions/moving_down_start.h"
#include "../../Common/include/Information/Actions/moving_up_start.h"
#include "../../Common/include/Information/Actions/shoot_stop.h"
#include "../../Common/include/Information/Actions/reload_stop.h"
#include "../../Common/include/Information/Actions/throw_stop.h"
#include "../../Common/include/Information/Actions/exit_stop.h"
#include "../../Common/include/Information/Actions/moving_right_stop.h"
#include "../../Common/include/Information/Actions/moving_left_stop.h"
#include "../../Common/include/Information/Actions/moving_down_stop.h"
#include "../../Common/include/Information/Actions/moving_up_stop.h"
#include "../../Common/include/Information/Actions/revive_start.h"
#include "../../Common/include/Information/Actions/revive_stop.h"

#define SEND_ACTION(action) actions_to_send.push(make_shared<action>())

EventHandler::EventHandler(
        Queue<std::shared_ptr<Information>> &actions_to_send,
        bool *quit, GameMusic& game_music) :
        actions_to_send(actions_to_send),
        game_music(game_music),
        quit(quit),
        event() ,
        keydown({nullptr}),
        keyup({nullptr}) {

    using std::make_shared;
    keydown.at(SDL_GetScancodeFromKey(SDLK_SPACE)) = make_shared<StartShootAction>();
    keydown.at(SDL_GetScancodeFromKey(SDLK_x)) = make_shared<StartThrowAction>();
    keydown.at(SDL_GetScancodeFromKey(SDLK_c)) = make_shared<StartChangeAction>();
    keydown.at(SDL_GetScancodeFromKey(SDLK_v)) = make_shared<StartReviveAction>();
    keydown.at(SDL_GetScancodeFromKey(SDLK_z)) = make_shared<StartReloadAction>();
    keydown.at(SDL_GetScancodeFromKey(SDLK_RIGHT)) = make_shared<StartMovingRightAction>();
    keydown.at(SDL_GetScancodeFromKey(SDLK_LEFT)) = make_shared<StartMovingLeftAction>();
    keydown.at(SDL_GetScancodeFromKey(SDLK_UP)) = make_shared<StartMovingUpAction>();
    keydown.at(SDL_GetScancodeFromKey(SDLK_DOWN)) = make_shared<StartMovingDownAction>();

    keyup.at(SDL_GetScancodeFromKey(SDLK_SPACE)) = make_shared<StopShootAction>();
    // keyup.at(SDL_GetScancodeFromKey(SDLK_c)) = make_shared<StopThrowAction>();
    keyup.at(SDL_GetScancodeFromKey(SDLK_v)) = make_shared<StopReviveAction>();
    keyup.at(SDL_GetScancodeFromKey(SDLK_z)) = make_shared<StopReloadAction>();
    keyup.at(SDL_GetScancodeFromKey(SDLK_RIGHT)) = make_shared<StopMovingRightAction>();
    keyup.at(SDL_GetScancodeFromKey(SDLK_LEFT)) = make_shared<StopMovingLeftAction>();
    keyup.at(SDL_GetScancodeFromKey(SDLK_UP)) = make_shared<StopMovingUpAction>();
    keyup.at(SDL_GetScancodeFromKey(SDLK_DOWN)) = make_shared<StopMovingDownAction>();

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
        shared_ptr<Information> exit(new StartExitAction());
        actions_to_send.push(exit);
        *quit = true;
    } else if (event.type == SDL_KEYDOWN) {

        if (event.key.keysym.sym == SDLK_ESCAPE) {
            shared_ptr<Information> exit(new StartExitAction());
            actions_to_send.push(exit);
            *quit = true;
            return;
        } else if (event.key.keysym.sym == SDLK_m) {
            game_music.changeMusicStatus();
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
