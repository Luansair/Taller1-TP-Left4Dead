//
// Created by luan on 05/06/23.
//

#ifndef TP_FEEDBACK_SERVER_GAMESTATE_H
#define TP_FEEDBACK_SERVER_GAMESTATE_H

#include "../Information/information.h"
#include "state_dto_element.h"

class GameStateFeedback : Information {
public:
    const std::vector<std::pair<std::uint32_t, ElementStateDTO>>&& elements;

    explicit GameStateFeedback(std::vector<
            std::pair<std::uint32_t,ElementStateDTO>
            >&& elements);

    [[nodiscard]] std::vector<int8_t> serialize() const override;
};

#endif //TP_FEEDBACK_SERVER_GAMESTATE_H
