//
// Created by luan on 22/06/23.
//

#ifndef TP_BACKGROUND_WAR_H
#define TP_BACKGROUND_WAR_H

#include <SDL2pp/Point.hh>
#include <SDL2pp/Renderer.hh>
#include "../../../Common/include/Information/information_code.h"

class WarBackground {

public:
    explicit WarBackground() = default;

    virtual void draw(std::uint8_t layer_type, const SDL2pp::Rect& destination) = 0;

    WarBackground(WarBackground&&) = delete;
    WarBackground& operator=(WarBackground&&) = delete;

    WarBackground(const WarBackground&) = delete;
    WarBackground& operator=(const WarBackground&) = delete;

    virtual ~WarBackground() = default;
};

#endif //TP_BACKGROUND_WAR_H
