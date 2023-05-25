#ifndef GAME_H_
#define GAME_H_

#include "command.h"
#include "game_state.h"
#include "../../libs/queue.h"
#include "../../libs/thread.h"

class Game : public Thread {
    // std::vector<std::uint8_t> admins;
    std::uint8_t max_players;
    std::uint8_t players_amount;

    Queue<Command> queue;
    std::vector<Queue<GameState>*> player_queues;
protected:
    virtual void run() override;

public:
    explicit Game(std::uint8_t max_players);

    // bool addAdmin(std::uint8_t player_id);

    bool join(Queue<Command>*& game_queue, Queue<GameState>*& player_queue,
              std::uint8_t* player_id);

    void stop();

    bool isEmpty() const;

    virtual ~Game() override = default;
};

#endif  // GAME_H_
