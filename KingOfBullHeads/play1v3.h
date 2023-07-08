#ifndef PLAY1V3_H
#define PLAY1V3_H

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
#include <vector>

class Play1v3:public QWidget{
    Q_OBJECT
public:
    explicit Play1v3(int n, QWidget* parent=0);
    ~Play1v3();
    void paintEvent(QPaintEvent *event);
    void click_Main_menu();
//    void mousePressEvent(QMouseEvent *event);
    MyPushButton* FinishImage;//成绩单
    MyPushButton* King = nullptr;  //牛头王
    MyPushButton* Gold = nullptr;  //金牌
    MyPushButton* Silver = nullptr;  //银牌
    MyPushButton* Bronze = nullptr;  //同袍
    MyPushButton* main_menu;  //主菜单
    MyPushButton* confirm_play_card;  //确认出牌
    MyPushButton* cancel_play_card;//取消这个决定
    MyPushButton* confirm_create_player;  //确认创建昵称
    MyPushButton* quit;  //主菜单中的退出游戏
    MyPushButton* finish_button;  //结束界面的按钮

    MyPlayer* ME;      //自己
    QLabel* MYLabel;//自己的名字

    MyPlayer* Bob;     //对手1
    QLabel* BobLabel;//对手1的名字

    MyPlayer* Carol;   //对手2
    QLabel* CarolLabel;//对手2的名字

    MyPlayer* Dave;    //对手3
    QLabel* DaveLabel;//对手3的名字

    QLabel* MYHeads;//记录牛头数
    QLabel* BobHeads;//记录牛头数
    QLabel* CarolHeads;//记录牛头数
    QLabel* DaveHeads;//记录牛头数

    QLabel* title;
    QLineEdit* lineEdit;

    int current_num;//每局游戏4小局，current_num记录当前为第几局
    //    QLabel* thisbackground;
    std::vector<int> Grade_list; //用vector表示成绩单
    //    QMovie* backgroundmovie;

    CardSlot* cardslot;
    CardSlot* line[4];
    CardSlot* buffer[4];//玩家选的牌和AI选的牌分别放在buffer[1]、buffer[2]、buffer[3]、buffer[4]中
    MyPushButton* toline1;
    MyPushButton* toline2;
    MyPushButton* toline3;
    MyPushButton* toline4;

    int whichmode;
    bool is_show_main_menu=0;

signals:
    void show_menu();
    void quit_game();
};

#endif // PLAY1V3_H
