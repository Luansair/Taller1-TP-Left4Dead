#ifndef GAME_H_
#define GAME_H_

#include <atomic>
#include "../../Common/include/Information/information.h"
#include "../../libs/queue.h"
#include "../../libs/thread.h"
#include "GameLogic/match.h"
#include "Command/command_ingame.h"
#include "../../Common/include/Information/information.h"

class Game : public Thread {
    // std::vector<std::uint8_t> admins;
    std::uint8_t max_players;
    std::atomic<std::uint8_t> players_amount;
    std::atomic<bool> is_running;
    std::atomic<bool> started;

    Queue<std::shared_ptr<InGameCommand>> commands_recv;
    std::vector<
      std::shared_ptr<
        Queue<std::shared_ptr<Information>>>> player_queues;

    Match match;

    std::mutex mtx;
protected:
    virtual void run() override;

public:
    explicit Game(std::uint8_t max_players);

    // bool addAdmin(std::uint8_t player_id);

    bool join(Queue<std::shared_ptr<InGameCommand>> *&game_queue, const std::shared_ptr<Queue<std::shared_ptr<Information>>> &player_queue,
              std::uint8_t* player_id);

    void stop();

    [[nodiscard]] bool isEmpty() const;

    ~Game() override;
};

#endif  // GAME_H_
