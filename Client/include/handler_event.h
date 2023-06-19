//
// Created by luan on 17/06/23.
//

#ifndef TP_HANDLER_EVENT_H
#define TP_HANDLER_EVENT_H

#include <memory>
#include <SDL2/SDL.h>
#include "../../Common/include/Information/information.h"
#include "../../libs/queue.h"

constexpr int MAX_INPUT_ID = SDL_NUM_SCANCODES;

class EventHandler {
    Queue<std::shared_ptr<Information>>& actions_to_send;

    bool* quit;
    SDL_Event event;
    /*
     * Un map tiene menos performance en run time y usa mas memoria para ints.
     * Un unordered map tiene mas performance en run time y usa menos memoria para hash simples (ints).
     * Varios arrays con todas las teclas posibles usa mas de 1500 bytes (1,5Kb)
     * Los arrays son O(1) como unordered map, no se cual consumira menos memoria.
     */
    std::array<std::shared_ptr<Information>, SDL_NUM_SCANCODES> keydown;
    std::array<std::shared_ptr<Information>, SDL_NUM_SCANCODES> keyup;
    // std::uint32_t event_type;
    // int key_code;

    void processEvent() const;
    // void processKeyDown() const;
    // void processKeyUp() const;
public:
    EventHandler(Queue<std::shared_ptr<Information>>& actions_to_send,
                 bool* quit);

    void start();
};
#endif //TP_HANDLER_EVENT_H
