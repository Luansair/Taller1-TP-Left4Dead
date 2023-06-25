/********************************************************************************
** Form generated from reading UI file 'lobbywindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOBBYWINDOW_H
#define UI_LOBBYWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_lobbywindow
{
public:

    void setupUi(QWidget *lobbywindow)
    {
        if (lobbywindow->objectName().isEmpty())
            lobbywindow->setObjectName(QString::fromUtf8("lobbywindow"));
        lobbywindow->resize(400, 300);

        retranslateUi(lobbywindow);

        QMetaObject::connectSlotsByName(lobbywindow);
    } // setupUi

    void retranslateUi(QWidget *lobbywindow)
    {
        lobbywindow->setWindowTitle(QCoreApplication::translate("lobbywindow", "lobbywindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class lobbywindow: public Ui_lobbywindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOBBYWINDOW_H
