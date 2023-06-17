//
// Created by luan on 17/06/23.
//

#ifndef TP_HANDLER_EVENT_H
#define TP_HANDLER_EVENT_H

#include <memory>
#include <SDL2/SDL.h>
#include "../../Common/include/Information/information.h"
#include "../../libs/queue.h"

class EventHandler {
    Queue<std::shared_ptr<Information>>& actions_to_send;

    bool* quit;

    SDL_Event event;
    // std::uint32_t event_type;
    // int key_code;

    void processEvent() const;
    void processKeyDown() const;
    void processKeyUp() const;
public:
    EventHandler(Queue<std::shared_ptr<Information>>& actions_to_send,
                 bool* quit);

    void start();
};
#endif //TP_HANDLER_EVENT_H
