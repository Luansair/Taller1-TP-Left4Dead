#ifndef GAMERESULTWINDOW_H
#define GAMERESULTWINDOW_H

#include <QWidget>
#include "../../../Common/include/Information/information.h"

namespace Ui {
class GameResultWindow;
}

class GameResultWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameResultWindow(const std::shared_ptr<Information> &info, QWidget *parent = nullptr);
    ~GameResultWindow();

private:
    const std::shared_ptr<Information>&info;
    Ui::GameResultWindow *ui;
};

#endif // GAMERESULTWINDOW_H
