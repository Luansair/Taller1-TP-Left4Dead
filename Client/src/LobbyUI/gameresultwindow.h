#ifndef GAMERESULTWINDOW_H
#define GAMERESULTWINDOW_H

#include <QWidget>
#include "../../../Common/include/Information/information.h"
#include "../../../Common/include/Information/feedback_server_score.h"

namespace Ui {
class GameResultWindow;
}

class GameResultWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameResultWindow(const GameScoreFeedback &score_feed, QWidget *parent = nullptr);
    ~GameResultWindow();

private slots:
    void on_pushButton_nextplayer_clicked();

    void on_pushButton_prevplayer_clicked();

private:
    const GameScoreFeedback& score_feed;
    std::uint8_t player_index;
    Ui::GameResultWindow *ui;

    void setStats();
};

#endif // GAMERESULTWINDOW_H
