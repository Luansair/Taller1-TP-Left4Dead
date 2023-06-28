#ifndef LOBBYWINDOW_H
#define LOBBYWINDOW_H

#include <QWidget>
#include <QPushButton>
#include "../../../Common/include/Information/information.h"
#include "../../../libs/queue.h"


namespace Ui {
class LobbyWindow;
}

class LobbyWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LobbyWindow(Queue<std::shared_ptr<Information>> &actions_to_send,
                         Queue<std::shared_ptr<Information>> &feedback_received, bool *joined,
                         QWidget *parent = nullptr);
    ~LobbyWindow();

private slots:

    void on_pushButton_creategame_clicked();

    void on_pushButton_joingame_clicked();

    void on_pushButton_p90soldier_clicked();

    void on_lineEdit_gamecode_textChanged(const QString &arg1);

    void on_pushButton_idfsoldier_clicked();

    void on_pushButton_scoutsoldier_clicked();

    void on_pushButton_survival_clicked();

    void on_pushButton_clearthezone_clicked();

    void on_pushButton_easy_clicked();

    void on_pushButton_normal_clicked();

    void on_pushButton_hard_clicked();

    void on_pushButton_insane_clicked();

    void on_pushButton_clicked();

private:
    Queue<std::shared_ptr<Information>>& actions_to_send;
    Queue<std::shared_ptr<Information>>& feedback_received;
    std::uint8_t game_type;
    std::uint8_t game_difficulty;
    std::uint8_t soldier_type;
    bool* joined;
    QPalette red_palette;
    QPalette green_palette;
    QPalette white_palette;
    Ui::LobbyWindow *ui;

    void create_game_process();

};

#endif // LOBBYWINDOW_H
