//
// Created by luan on 22/06/23.
//

#ifndef TP_BACKGROUND_MANAGER_H
#define TP_BACKGROUND_MANAGER_H

#include "background_war1.h"
#include "background_war.h"

class BackgroundManager {
    War1Background war1_background;
    //War2Background war2_background;
    //War3Background war3_background;
    //War4Background war4_background;

    std::array<WarBackground*, BACKGROUND_TYPE_LAST> backgrounds;
public:
    explicit BackgroundManager(SDL2pp::Renderer& renderer);

    // Necesito el rectangulo con un alto y ancho calculado previamente segun el windows size.
    void drawLayer(std::uint8_t background_type, std::uint8_t layer_type, const SDL2pp::Rect& destination);
    // void drawElement();
};

#endif //TP_BACKGROUND_MANAGER_H
