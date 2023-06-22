#ifndef GAME_H_
#define GAME_H_

#include <atomic>
#include "../../Common/include/Information/information.h"
#include "../../libs/queue.h"
#include "../../libs/thread.h"
#include "GameLogic/match.h"
#include "GameLogic/survival.h"
#include "GameLogic/clearthezone.h"
#include "Command/command_ingame.h"
#include "../../Common/include/Information/information.h"

class Game : public Thread {
    // std::vector<std::uint8_t> admins;
    std::uint8_t max_players;
    std::atomic<std::uint8_t> players_amount;
    std::atomic<bool> is_running;
    std::atomic<bool> started;
    uint8_t actor = 0;
    //uint8_t zactor = 3;
    bool zombies = false;

    Queue<std::shared_ptr<InGameCommand>> commands_recv;
    std::vector<
      std::shared_ptr<
        Queue<std::shared_ptr<Information>>>> player_queues;

    std::shared_ptr<Match> match;

    std::mutex mtx;
protected:
    virtual void run() override;

public:
    explicit Game(std::uint8_t max_players, uint8_t gameMode);

    // bool addAdmin(std::uint8_t player_id);
    [[nodiscard]] bool isFull() const;

    void join(Queue<std::shared_ptr<InGameCommand>> *&game_queue, const std::shared_ptr<Queue<std::shared_ptr<Information>>> &player_queue,
              std::uint8_t* player_id);
    
    void selectMode(uint8_t gameMode);

    void stop();

    [[nodiscard]] bool isEmpty() const;

    ~Game() override;
};

#endif  // GAME_H_
