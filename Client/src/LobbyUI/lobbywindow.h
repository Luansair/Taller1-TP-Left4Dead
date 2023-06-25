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
    explicit LobbyWindow(
            Queue<std::shared_ptr<Information>>& actions_to_send,
            Queue<std::shared_ptr<Information>>& feedback_received,
            QWidget *parent = nullptr);
    ~LobbyWindow();

private slots:
    void on_pushButton_clicked();


private:
    Queue<std::shared_ptr<Information>>& actions_to_send;
    Queue<std::shared_ptr<Information>>& feedback_received;
    Ui::LobbyWindow *ui;
};

#endif // LOBBYWINDOW_H
