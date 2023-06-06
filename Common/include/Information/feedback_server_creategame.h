//
// Created by luan on 04/06/23.
//

#ifndef TP_FEEDBACK_SERVER_CREATEGAME_H
#define TP_FEEDBACK_SERVER_CREATEGAME_H

#include "../Information/information.h"
// PreGameCommand puede recibir la Queue del Send para pushear info.
// De hecho recibe la queue del player c:
// Entonces puede devolver el booleano y listo. Sin grandes cambios
class CreateGameFeedback : public Information {

public:
    std::uint32_t game_code;

    explicit CreateGameFeedback(std::uint32_t game_code);

    [[nodiscard]] virtual std::vector<std::int8_t> serialize() const override;
};


#endif //TP_FEEDBACK_SERVER_CREATEGAME_H
