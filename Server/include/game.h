#ifndef GAME_H_
#define GAME_H_

#include <atomic>
#include "game_state.h"
#include "../../libs/queue.h"
#include "../../libs/thread.h"
#include "GameLogic/match.h"
#include "Command/command.h"

class Game : public Thread {
    // std::vector<std::uint8_t> admins;
    std::uint8_t max_players;
    std::uint8_t players_amount;
    std::atomic<bool> is_running;

    Queue<Command*> commands_recv;
    std::vector<Queue<GameState*>*> player_queues;

    Match match;
protected:
    virtual void run() override;

public:
    explicit Game(std::uint8_t max_players);

    // bool addAdmin(std::uint8_t player_id);

    bool join(Queue<Command *> *&game_queue, Queue<GameState *> &player_queue,
              std::uint8_t* player_id);

    void stop();

    bool isEmpty() const;

    virtual ~Game() override;
};

#endif  // GAME_H_
