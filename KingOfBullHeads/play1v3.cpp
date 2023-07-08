#include "play1v3.h"

Play1v3::Play1v3(int n, QWidget* parent):QWidget(parent),current_num(0),whichmode(n)
{
    title = new QLabel(parent);
    title->setText("Create a Player");
    title->setFixedSize(600,200);
    title->setStyleSheet("font-size: 60px");
    title->setAlignment(Qt::AlignCenter);
    title->move(480,350);
    title->show();
    //输入昵称
    lineEdit = new QLineEdit(this);
    lineEdit->move(400, 700);
    lineEdit->setFixedWidth(600);
    lineEdit->setFixedHeight(80);
    lineEdit->setStyleSheet("font-size: 35px");
    lineEdit->setPlaceholderText("请输入昵称...");
    lineEdit->setClearButtonEnabled(true);
    //创建主菜单和创建角色
    main_menu = new MyPushButton(this, 0, ":/button/button06.png", ":/button/button06.png");
    //confirm_play_card = new MyPushButton(this, "PlayCard");
    confirm_create_player = new MyPushButton(this, 0, ":/button/button11.png", ":/button/button11.png");
    confirm_create_player->resize(200,80);
    //confirm_create_player->setFixedHeight(80);
    quit = new MyPushButton(this, 0, ":/button/button00.png", ":/button/button00.png");
    quit->resize(300, 100);
    quit->move(1365, 100);
    main_menu->resize(300, 100);
    main_menu->move(1365, 0);
    //confirm_create_player->resize(150, 50);
    confirm_create_player->move(1020, 700);
    //confirm_play_card->hide();
    quit->hide();
    //创建角色和其名字及得分计数器
    ME = new MyPlayer(parent,"Alice",":/res/Res/Alice.jpg");
    ME->move(0, 764);
    ME->hide();
    MYLabel = new QLabel(parent);
    MYLabel->setFixedWidth(130);
    MYLabel->setFixedHeight(50);
    MYLabel->move(150,830);

    Bob = new MyPlayer(parent,"Bob",":/res/Res/Bob.jpg");
    Bob->move(0, 0);
    Bob->hide();
    BobLabel = new QLabel(parent);
    BobLabel->setFixedWidth(130);
    BobLabel->setFixedHeight(50);
    BobLabel->move(150,70);

    Carol = new MyPlayer(this,"Carol",":/res/Res/Carol.jpg");
    Carol->move(0, 255);
    Carol->hide();
    CarolLabel = new QLabel(parent);
    CarolLabel->setFixedWidth(130);
    CarolLabel->setFixedHeight(50);
    CarolLabel->move(150,303);

    Dave = new MyPlayer(this,"Dave",":/res/Res/Dave.jpg");
    Dave->move(0, 510);
    Dave->hide();
    DaveLabel = new QLabel(parent);
    DaveLabel->setFixedWidth(130);
    DaveLabel->setFixedHeight(50);
    DaveLabel->move(150,586);

    MYHeads = new QLabel(parent);
    MYHeads->setFixedSize(100,60);
    MYHeads->move(150,770);
    BobHeads = new QLabel(parent);
    BobHeads->setFixedSize(100,60);
    BobHeads->move(150,10);
    CarolHeads = new QLabel(parent);
    CarolHeads->setFixedSize(100,60);
    CarolHeads->move(150,243);
    DaveHeads = new QLabel(parent);
    DaveHeads->setFixedSize(100,60);
    DaveHeads->move(150,526);

    //卡片槽和四行
    cardslot = new CardSlot(parent,0,920,1600,320);// 可以将最后一个参数删掉，用默认的(black利于观察)
    line[0] = new CardSlot(parent,300,0,640,200);
    line[1] = new CardSlot(parent,300,210,640,200);
    line[2] = new CardSlot(parent,300,420,640,200);
    line[3] = new CardSlot(parent,300,630,640,200);

    //四个缓冲区
    buffer[0] = new CardSlot(parent,1200,500,160,250);
    buffer[1] = new CardSlot(parent,1200,200,160,250);
    buffer[2] = new CardSlot(parent,1400,200,160,250);
    buffer[3] = new CardSlot(parent,1400,500,160,250);

    //确认、取消出牌按钮
    confirm_play_card = new MyPushButton(this, 0, ":/button/button15.png", ":/button/button15.png");
    confirm_play_card->setFixedSize(120,70);
    confirm_play_card->move(1000,820);
    cancel_play_card = new MyPushButton(this, 0, ":/button/button16.png", ":/button/button16.png");
    cancel_play_card->setFixedSize(120,70);
    cancel_play_card->move(1200,820);
    confirm_play_card->hide();
    cancel_play_card->hide();
    //结束界面按钮
    finish_button = new MyPushButton(this, 0, ":/button/button14.png", ":/button/button14.png");
    finish_button->setFixedSize(250, 100);
    finish_button->move(680, 800);
    finish_button->hide();
    //选择行按钮
    toline1 = new MyPushButton(this, 1, ":/button/chooseline(1).png", ":/button/chooseline.png");
    toline1->resize(75, 75);
    toline1->setStyleSheet("font-size: 25px");
    toline1->move(980, 80);
    toline1->hide();

    toline2 = new MyPushButton(this, 1, ":/button/chooseline(1).png", ":/button/chooseline.png");
    toline2->resize(75, 75);
    toline2->setStyleSheet("font-size: 25px");
    toline2->move(980, 290);
    toline2->hide();

    toline3 = new MyPushButton(this, 1, ":/button/chooseline(1).png", ":/button/chooseline.png");
    toline3->resize(75, 75);
    toline3->setStyleSheet("font-size: 25px");
    toline3->move(980, 500);
    toline3->hide();

    toline4 = new MyPushButton(this, 1, ":/button/chooseline(1).png", ":/button/chooseline.png");
    toline4->resize(75, 75);
    toline4->setStyleSheet("font-size: 25px");
    toline4->move(980, 710);
    toline4->hide();


}

void Play1v3::click_Main_menu(){
    if(!is_show_main_menu){
        quit->show();
        is_show_main_menu=1;
    }
    else{
        is_show_main_menu=0;
        quit->hide();
    }
}

void Play1v3::paintEvent(QPaintEvent *event){
    QWidget::paintEvent(event);

    QPainter painter(this);

    // 加载照片文件
    QImage image(":/res/Res/playbackground.png");
    // 在绘图设备上绘制照片
    painter.drawImage(rect(), image);
}
Play1v3::~Play1v3()
{
    delete main_menu;  //主菜单
    delete confirm_create_player;  //确认创建昵称
    delete quit;  //主菜单中的退出游戏
    delete ME;  //自己
    delete Bob;  //对方
    delete lineEdit;
    delete title;
    delete MYLabel;
    delete BobLabel;
    delete CarolLabel;
    delete DaveLabel;

    delete MYHeads;
    delete BobHeads;
    delete CarolHeads;
    delete DaveHeads;

    delete cardslot;
    delete line[0];
    delete line[1];
    delete line[2];
    delete line[3];
    delete toline1;
    delete toline2;
    delete toline3;
    delete toline4;
    delete buffer[0];
    delete buffer[1];
    delete buffer[2];
    delete buffer[3];
    delete confirm_play_card;
    delete cancel_play_card;
}
