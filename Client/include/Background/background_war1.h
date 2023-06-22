//
// Created by luan on 22/06/23.
//

#ifndef TP_BACKGROUND_WAR1_H
#define TP_BACKGROUND_WAR1_H

#include "background_war.h"
#include "background_layer.h"

class War1Background : public WarBackground {
    std::array<Layer, WAR_1_LAYER_LAST> layers;

public:
    explicit War1Background(SDL2pp::Renderer& renderer);

    void draw(std::uint8_t layer_type, const SDL2pp::Rect& destination) override;

    War1Background(War1Background&&) = delete;
    War1Background& operator=(War1Background&&) = delete;

    War1Background(const War1Background&) = delete;
    War1Background& operator=(const War1Background&) = delete;

    ~War1Background() override = default;
};

#endif //TP_BACKGROUND_WAR1_H
