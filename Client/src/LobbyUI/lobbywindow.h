//
// Created by luan on 24/06/23.
//

#ifndef TP_LOBBYWINDOW_H
#define TP_LOBBYWINDOW_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class lobbywindow; }
QT_END_NAMESPACE

class lobbywindow : public QWidget {
    Q_OBJECT

public:
    explicit lobbywindow(QWidget *parent = nullptr);

    virtual ~lobbywindow() override;

private:
    Ui::lobbywindow *ui;
};


#endif //TP_LOBBYWINDOW_H
