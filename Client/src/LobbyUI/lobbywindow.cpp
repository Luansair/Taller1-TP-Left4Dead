#include "lobbywindow.h"
//#include "../../../build/ui_lobbywindow.h"
#include "./ui_lobbywindow.h"

LobbyWindow::LobbyWindow(QWidget *parent) :
    QWidget(parent),
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

