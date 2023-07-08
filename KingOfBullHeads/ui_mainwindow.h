/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <QtWidgets/QStackedWidget>
#include "beginscene.h"
#include "choosemode.h"
#include "rule.h"
#include "settings.h"
#include "Guy2PlayModeChoose.h"
#include "Guy4PlayModeChoose.h"
#include "play1v1.h"
#include "play1v3.h"
#include "card.h"
#include "StayTuned.h"
#include "GradeList.h"
//#include "finishscene.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QLabel *name_label = NULL;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QStackedWidget *stackedWidget;
    BeginScene *beginscene;
    ChooseModeScene *choosemodescene;
    RuleScene *rulescene;
    SettingScene* settingscene;
    Guy2PlayModeChoose *Guy2modescene;
    Guy4PlayModeChoose *Guy4modescene;
    Play1v1 *play1v1scene;
    Play1v3 *play1v3scene;
    MyCard *current_choose_card = nullptr;//指向当前点击的card
    StayTuned *staytuned;
    GradeList *gradelist;
//    FinishScene *finishScene;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1600, 1200);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/res/Res/Icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        stackedWidget = new QStackedWidget(centralwidget);
        beginscene = new BeginScene();
        beginscene->resize(1600,1200);
        stackedWidget->resize(1600,1200);
        stackedWidget->addWidget(beginscene);
        QVBoxLayout* Layout = new QVBoxLayout(centralwidget);
        Layout->addWidget(stackedWidget);
        //Layout->setSpacing(1);
        //Layout->setContentsMargins(11, 11, 11, 11);
        Layout->setObjectName(QString::fromUtf8("verticalLayout"));
        Layout->setContentsMargins(0, 0, 0, 0);
        centralwidget->setLayout(Layout);
        retranslateUi(MainWindow);
        stackedWidget->setCurrentIndex(0);
        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
