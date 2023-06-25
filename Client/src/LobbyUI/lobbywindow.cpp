
#include <string>
#include <iostream>
#include <QLineEdit>
#include <QIntValidator>

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
    ui->lineEdit_gamecode->setValidator(new QIntValidator(1000000, 9999999, this));

}

LobbyWindow::~LobbyWindow()
{
    delete ui;
}

void LobbyWindow::on_pushButton_creategame_clicked()
{

}


void LobbyWindow::on_pushButton_joingame_clicked()
{
    bool succesful_conversion;

    std::uint32_t game_code = ui->lineEdit_gamecode->displayText().toUInt(&succesful_conversion);

    if (!succesful_conversion) {
        throw std::runtime_error("LobbyWindow::on_pushButton_joingame_clicked(). QString to type Uint conversion failed.\n");
    }

}

