#include <string>
#include <iostream>
#include <QLineEdit>
#include <QIntValidator>

#include "lobbywindow.h"
#include "ui_lobbywindow.h"
#include "../../../Common/include/Information/Actions/game_join.h"
#include "../../../Common/include/Information/feedback_server_joingame.h"
#include "../../../Common/include/Information/Requests/pick_soldier_p90.h"
#include "../../../Common/include/Information/Requests/pick_soldier_idf.h"
#include "../../../Common/include/Information/Requests/pick_soldier_scout.h"
#include "../../../Common/include/Information/Actions/game_create.h"
#include "../../../Common/include/Information/feedback_server_creategame.h"

enum Page : std::uint8_t {
    PAGE_MAIN,
    PAGE_GAMECODE,
    PAGE_PICKSOLDIER,
    PAGE_PICKGAMETYPE,
    PAGE_PICKGAMEDIFF
};

LobbyWindow::LobbyWindow(Queue<std::shared_ptr<Information>> &actions_to_send,
                         Queue<std::shared_ptr<Information>> &feedback_received, bool *joined, QWidget *parent) :
                         QWidget(parent),
                         actions_to_send(actions_to_send),
                         feedback_received(feedback_received),
                         joined(joined),
                         red_palette(),
                         green_palette(),
                         white_palette(),
                         ui(new Ui::LobbyWindow)
{
    ui->setupUi(this);
    ui->lineEdit_gamecode->setValidator(new QIntValidator(1000000, 9999999, this));
    ui->stackedWidget->setCurrentIndex(PAGE_MAIN);
    red_palette.setColor(QPalette::Base, Qt::red);
    green_palette.setColor(QPalette::Base, Qt::green);
    white_palette.setColor(QPalette::Base, Qt::white);
    QPixmap bkgnd(RESOURCES_PATH "/Lobby/lobbyimage.jpeg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

}

LobbyWindow::~LobbyWindow()
{
    delete ui;
}

void LobbyWindow::on_pushButton_creategame_clicked()
{
    ui->stackedWidget->setCurrentIndex(PAGE_PICKGAMETYPE);
}


void LobbyWindow::on_pushButton_joingame_clicked()
{
    bool succesful_conversion;

    std::uint32_t game_code = ui->lineEdit_gamecode->displayText().toUInt(&succesful_conversion);

    if (!succesful_conversion) {
        ui->lineEdit_gamecode->setPalette(red_palette);
        
    } else {
        actions_to_send.push(std::make_shared<JoinGameAction>(game_code));
        const auto& feed = feedback_received.pop();
        const auto& join_feed = dynamic_cast<JoinGameFeedback&>(*feed);
        if (join_feed.joined == NOT_JOINED) {
            ui->lineEdit_gamecode->setPalette(red_palette);
        } else {
            ui->stackedWidget->setCurrentIndex(PAGE_PICKSOLDIER);
        }
    }

}


void LobbyWindow::on_pushButton_p90soldier_clicked()
{
    soldier_type = REQUEST_PICK_P90_SOLDIER;
    actions_to_send.push(std::make_shared<PickP90SoldierRequest>());
    *joined = true;
    this->close();
}


void LobbyWindow::on_lineEdit_gamecode_textChanged(const QString &arg1)
{
    auto pallete = QPalette();
    pallete.setColor(QPalette::Base, Qt::white);
    ui->lineEdit_gamecode->setPalette(pallete);
}

void LobbyWindow::on_pushButton_idfsoldier_clicked() {
    soldier_type = REQUEST_PICK_IDF_SOLDIER;
    actions_to_send.push(std::make_shared<PickIdfSoldierRequest>());
    *joined = true;
    this->close();
}

void LobbyWindow::on_pushButton_scoutsoldier_clicked() {
    soldier_type = REQUEST_PICK_SCOUT_SOLDIER;
    actions_to_send.push(std::make_shared<PickScoutSoldierRequest>());
    *joined = true;
    this->close();
}

void LobbyWindow::on_pushButton_survival_clicked() {
    game_type = REQUEST_SURVIVAL;
    ui->stackedWidget->setCurrentIndex(PAGE_PICKGAMEDIFF);
}

void LobbyWindow::on_pushButton_clearthezone_clicked() {
    game_type = REQUEST_CLEAR_THE_ZONE;
    ui->stackedWidget->setCurrentIndex(PAGE_PICKGAMEDIFF);
}

void LobbyWindow::on_pushButton_easy_clicked()
{
    game_difficulty = REQUEST_EASY;
    create_game_process();
}


void LobbyWindow::on_pushButton_normal_clicked()
{
    game_difficulty = REQUEST_NORMAL;
    create_game_process();
}


void LobbyWindow::on_pushButton_hard_clicked()
{
    game_difficulty = REQUEST_HARD;
    create_game_process();
}


void LobbyWindow::on_pushButton_insane_clicked()
{
    game_difficulty = REQUEST_INSANE;
    create_game_process();
}

void LobbyWindow::create_game_process() {
    ui->stackedWidget->setCurrentIndex(PAGE_GAMECODE);
    actions_to_send.push(std::make_shared<CreateGameAction>(game_type, game_difficulty));
    const auto& feed = feedback_received.pop();
    std::uint32_t game_code = dynamic_cast<CreateGameFeedback&>(*feed).game_code;
    ui->lineEdit_gamecoderecv->setText(QString::number(game_code));

}


void LobbyWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(PAGE_PICKSOLDIER);
}

