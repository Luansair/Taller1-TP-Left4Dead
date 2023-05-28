#ifndef GAME_H_
#define GAME_H_

#include "Command/command.h"
#include "game_state.h"
#include "../../libs/queue.h"
#include "../../libs/thread.h"

class Game : public Thread {
    // std::vector<std::uint8_t> admins;
    std::uint8_t max_players;
    std::uint8_t players_amount;

    Queue<Command*> commands_recv;
    std::vector<Queue<GameState*>*> player_queues;
protected:
    virtual void run() override;

public:
    explicit Game(std::uint8_t max_players);

    // bool addAdmin(std::uint8_t player_id);

    bool join(Queue<Command *> *&game_queue, Queue<GameState *> &player_queue,
              std::uint8_t* player_id);

    void shoot(uint8_t player_id, uint8_t state);

    void move(uint8_t player_id,
            uint8_t state,
            uint8_t moveAxis,
            int8_t MoveDirection,
            uint8_t moveForce);

    void reload(uint8_t player_id, uint8_t state);

    void cgrenade(uint8_t player_id);

    void throwgrenade(uint8_t player_id);

    void stop();

    bool isEmpty() const;

    virtual ~Game() override;
};

#endif  // GAME_H_
