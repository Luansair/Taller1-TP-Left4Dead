#include "lobbywindow.h"
//#include "../../../build/ui_lobbywindow.h"
#include "ui_lobbywindow.h"

LobbyWindow::LobbyWindow(Queue<std::shared_ptr<Information>>& actions_to_send,
                         Queue<std::shared_ptr<Information>>& feedback_received,
                         QWidget *parent) :
                         QWidget(parent),
                         actions_to_send(actions_to_send),
                         feedback_received(feedback_received),
                         ui(new Ui::LobbyWindow)
{
    ui->setupUi(this);
}

LobbyWindow::~LobbyWindow()
{
    delete ui;
}

void LobbyWindow::on_pushButton_clicked()
{

}


void LobbyWindow::on_pushButton_creategame_clicked()
{

}


void LobbyWindow::on_pushButton_joingame_clicked()
{

}

