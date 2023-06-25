#ifndef LOBBYWINDOW_H
#define LOBBYWINDOW_H

#include <QWidget>

namespace Ui {
class LobbyWindow;
}

class LobbyWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LobbyWindow(QWidget *parent = nullptr);
    ~LobbyWindow();

private slots:
    void on_pushButton_clicked();


private:
    Ui::LobbyWindow *ui;
};

#endif // LOBBYWINDOW_H
