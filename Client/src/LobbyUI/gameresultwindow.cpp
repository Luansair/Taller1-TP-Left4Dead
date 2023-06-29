#include "gameresultwindow.h"
#include "ui_gameresultwindow.h"
#include "../../../Common/include/Information/feedback_server_score.h"


GameResultWindow::GameResultWindow(const GameScoreFeedback &score_feed, QWidget *parent) :
    QWidget(parent),
    score_feed(score_feed),
    player_index(0),
    ui(new Ui::GameResultWindow)
{
    if (score_feed.score.empty()) {
        this->close();
    }
    ui->setupUi(this);
    QPixmap bkgnd(RESOURCES_PATH "/Lobby/lobbyimage.jpeg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
    setStats();
}

GameResultWindow::~GameResultWindow()
{
    delete ui;
}

/*
void GameVisual::loadScoreInfo(const GameScoreFeedback& feed) {
    for (auto & pair_id_score : feed.score) {
        std::uint16_t player_id = pair_id_score.first;
        const ScoreDTO& score = pair_id_score.second;
        drawer_manager.loadScore(player_id, score);
    }
}

void
DrawerManager::loadScore(std::uint16_t player_id, const ScoreDTO &score) {
    //aca cargar la info
    std::cout << "player_id: " << player_id << "\n";
    std::cout << "seconds_alive: " << score.seconds_alive << "\n";
    std::cout << "kills: " << score.kills << "\n";
    std::cout << "bullets_fired: " << score.bullets_fired << "\n";
    std::cout << "------------------------------------------------\n";
}
 */
void GameResultWindow::on_pushButton_nextplayer_clicked()
{
    if (player_index == score_feed.score.size() - 1) {
        player_index = 0;
    } else {
        player_index++;
    }
    setStats();
}


void GameResultWindow::on_pushButton_prevplayer_clicked()
{

    if (player_index == 0) {
        player_index = score_feed.score.size() - 1;
    } else {
        player_index--;
    }
    setStats();
}

void GameResultWindow::setStats() {
    ui->lineEdit_playerid->setText(QString::number(score_feed.score.at(player_index).first));
    ui->lineEdit_timealive->setText(QString::number(score_feed.score.at(player_index).second.seconds_alive));
    ui->lineEdit_kills->setText(QString::number(score_feed.score.at(player_index).second.kills));
    ui->lineEdit_bulletsfired->setText(QString::number(score_feed.score.at(player_index).second.bullets_fired));
}

