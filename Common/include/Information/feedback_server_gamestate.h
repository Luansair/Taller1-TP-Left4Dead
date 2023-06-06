//
// Created by luan on 05/06/23.
//

#ifndef TP_FEEDBACK_SERVER_GAMESTATE_H
#define TP_FEEDBACK_SERVER_GAMESTATE_H

#include "../Information/information.h"
#include "state_dto_element.h"

class GameStateFeedback : Information {
public:
    const std::vector<std::pair<std::uint32_t, ElementStateDTO>> elements;
};

#endif //TP_FEEDBACK_SERVER_GAMESTATE_H
