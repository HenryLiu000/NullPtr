#ifndef PLAY1V1_H
#define PLAY1V1_H

#include <QWidget>
#include <QSound>
#include <QLabel>
#include <QMovie>
#include <QPropertyAnimation>
#include <QTimer>
#include <QDebug>
#include <QPainter>
#include <QImage>
#include <QLineEdit>
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPalette>
#include "MyPushButton.h"
#include "player.h"
#include "cardslot.h"

class Play1v1:public QWidget{
    Q_OBJECT
public:
    explicit Play1v1(int n,QWidget* parent=0);
    ~Play1v1();
    void paintEvent(QPaintEvent *event);
    void click_Main_menu();
    MyPushButton* FinishImage = nullptr; //结束画面
    MyPushButton* main_menu;  //主菜单
    MyPushButton* confirm_play_card;  //确认出牌
    MyPushButton* cancel_play_card;//取消这个决定
    MyPushButton* confirm_create_player;  //确认创建昵称
    MyPushButton* quit;  //主菜单中的退出游戏
    MyPushButton* finish_button;  //结束界面的按钮

    MyPlayer* ME;  //自己
    QLabel* MYLabel;//自己的名字

    MyPlayer* Bob;  //对方
    QLabel* BobLabel;//对方的名字

    QLabel* MYHeads;//记录牛头数
    QLabel* BobHeads;//记录牛头数

    QLineEdit* lineEdit;
    QLabel* title;
//    QLabel* thisbackground;
    QLabel* who_wins;
//    QMovie* backgroundmovie;
    CardSlot* cardslot;
    CardSlot* line[4];
    CardSlot* buffer[2];//玩家选的牌和AI选的牌分别放在buffer[1]、buffer[2]中

    MyPushButton* toline1;
    MyPushButton* toline2;
    MyPushButton* toline3;
    MyPushButton* toline4;

    int whichmode;//0:Easy 1:normal 2:hard
    bool is_show_main_menu=0;

signals:
    void show_menu();
    void quit_game();
};

#endif // PLAY1V1_H
