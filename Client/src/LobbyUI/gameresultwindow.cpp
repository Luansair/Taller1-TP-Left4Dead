#include "gameresultwindow.h"
#include "ui_gameresultwindow.h"


GameResultWindow::GameResultWindow(const std::shared_ptr<Information> &info, QWidget *parent) :
    QWidget(parent),
    info(info),
    ui(new Ui::GameResultWindow)
{
    ui->setupUi(this);
}

GameResultWindow::~GameResultWindow()
{
    delete ui;
}
