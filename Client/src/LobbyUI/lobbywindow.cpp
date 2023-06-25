//
// Created by luan on 24/06/23.
//

// You may need to build the project (run Qt uic code generator) to get "ui_lobbywindow.h" resolved

#include "lobbywindow.h"
#include "ui_lobbywindow.h"


lobbywindow::lobbywindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::lobbywindow) {
    ui->setupUi(this);
}

lobbywindow::~lobbywindow() {
    delete ui;
}
