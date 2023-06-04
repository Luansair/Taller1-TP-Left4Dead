//
// Created by luan on 04/06/23.
//

#ifndef TP_FEEDBACK_SERVER_CREATEGAME_H
#define TP_FEEDBACK_SERVER_CREATEGAME_H

#include "feedback_server.h"
// PreGameCommand puede recibir la Queue del Send para pushear info.
// De hecho recibe la queue del player c:
// Entonces puede devolver el booleano y listo. Sin grandes cambios
class CreateGameFeedback : public ServerFeedback {
    std::uint32_t game_code;
public:
    explicit CreateGameFeedback(std::uint32_t game_code);

    [[nodiscard]] virtual std::vector<std::int8_t> serialize() const override;
};


#endif //TP_FEEDBACK_SERVER_CREATEGAME_H
