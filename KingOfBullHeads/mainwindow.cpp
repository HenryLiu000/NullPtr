#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "MyPushButton.h"
#include <QDebug>
#include <QMediaPlayer>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <beginscene.h>
#include <Myalgorithm/GiveCardAlgorithm.h>
#include <Myalgorithm/AIChooseCard.h>
#include <algorithm>
#include <QFile>
#include <QDataStream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/res/Res/Icon.ico"));
    setWindowTitle("Who is the king of bull heads?");
    ui->stackedWidget->setCurrentIndex(0);
    //ui->stackedWidget->show();
    //Start
    connect(ui->beginscene->start,&MyPushButton::clicked,this,&MainWindow::Start_Clicked);
    //Setting
    connect(ui->beginscene->setting,&MyPushButton::clicked,this,&MainWindow::Setting_Clicked);
    //Rule
    connect(ui->beginscene->rule,&MyPushButton::clicked,this,&MainWindow::Rule_Clicked);
    //Quitgame
    connect(ui->beginscene->Quitgame,&MyPushButton::clicked,this,&MainWindow::Quitgame_Clicked);
    //Renew
    connect(ui->beginscene->Renew, &MyPushButton::clicked, this, &MainWindow::RenewInfo);
}
void MainWindow::Start_Clicked()
{
    ui->choosemodescene = new ChooseModeScene(ui->centralwidget);
    ui->stackedWidget->addWidget(ui->choosemodescene);
    ui->stackedWidget->setCurrentIndex(1);
    connect(ui->choosemodescene->Quit,&MyPushButton::clicked,this,&MainWindow::QuitChooseMode_Clicked);
    connect(ui->choosemodescene->Guy2,&MyPushButton::clicked,this,&MainWindow::Guy2Choose);
    connect(ui->choosemodescene->Guy4,&MyPushButton::clicked,this,&MainWindow::Guy4Choose);
}

//MainMenu按钮
void MainWindow::Setting_Clicked()  // 设置
{
    ui->settingscene = new SettingScene(ui->centralwidget);
    ui->stackedWidget->addWidget(ui->settingscene);
    ui->stackedWidget->setCurrentIndex(1);
    connect(ui->settingscene->Quit,&MyPushButton::clicked,this,&MainWindow::QuitChooseMode_Clicked);
}
void MainWindow::Rule_Clicked()     // 规则
{
    ui->rulescene = new RuleScene(ui->centralwidget);
    ui->stackedWidget->addWidget(ui->rulescene);
    ui->stackedWidget->setCurrentIndex(1);
    connect(ui->rulescene->Quit,&MyPushButton::clicked,this,&MainWindow::QuitChooseMode_Clicked);
}

void MainWindow::RenewInfo()   //更新信息
{
    //导入储存信息
    QFile *file = new QFile("game_progress.txt");
    if (!file->open(QIODevice::ReadOnly)) {
        qDebug() << "something wrong!" ;
    }
    QDataStream in(file);
    in >> ui->beginscene->Kingnum >> ui->beginscene->Totalnum >> ui->beginscene->Exp >> ui->beginscene->Level;
    file->close();
    ui->beginscene->info = new QLabel(this);
    ui->beginscene->info->setText("总胜场：\n"
    "总场数：\n");
    QString labelText = QString::number(ui->beginscene->Kingnum);
    ui->beginscene->kingnum->setText(labelText);
    labelText = QString::number(ui->beginscene->Totalnum);
    ui->beginscene->totalnum->setText(labelText);
    ui->beginscene->kingnum->show();
    ui->beginscene->totalnum->show();
    labelText = QString::number(ui->beginscene->Exp);
    ui->beginscene->exp->setText(labelText);
    ui->beginscene->exp->show();
    labelText = QString::number(ui->beginscene->Level);
    ui->beginscene->level->setText(labelText);
    ui->beginscene->level->show();
}

void MainWindow::Quitgame_Clicked()
{
    delete ui->stackedWidget->widget(0);
    this->close();
}
void MainWindow::QuitChooseMode_Clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    delete ui->stackedWidget->widget(1);
}

//人数选择按钮
void MainWindow::Guy2Choose()
{
    ui->Guy2modescene = new Guy2PlayModeChoose(ui->centralwidget);
    ui->stackedWidget->addWidget(ui->Guy2modescene);
    ui->stackedWidget->setCurrentIndex(2);
    connect(ui->Guy2modescene->MainMenu,&MyPushButton::clicked,this,&MainWindow::Guy2ChooseReturnToMainMenu);
    connect(ui->Guy2modescene->Return,&MyPushButton::clicked,this,&MainWindow::Guy2ChooseReturnToChooseMode);

    connect(ui->Guy2modescene->Easy, &MyPushButton::clicked, this, &MainWindow::EasyPlay1v1);
    connect(ui->Guy2modescene->Medium, &MyPushButton::clicked, this, &MainWindow::NormalPlay1v1);
    connect(ui->Guy2modescene->Hard, &MyPushButton::clicked, this, &MainWindow::HardPlay1v1);

}
void MainWindow::Guy4Choose()
{
    ui->Guy4modescene = new Guy4PlayModeChoose(ui->centralwidget);
    ui->stackedWidget->addWidget(ui->Guy4modescene);
    ui->stackedWidget->setCurrentIndex(2);
    connect(ui->Guy4modescene->MainMenu,&MyPushButton::clicked,this,&MainWindow::Guy2ChooseReturnToMainMenu);
    connect(ui->Guy4modescene->Return,&MyPushButton::clicked,this,&MainWindow::Guy2ChooseReturnToChooseMode);
    connect(ui->Guy4modescene->Easy, &MyPushButton::clicked, this, &MainWindow::EasyPlay1v3);

    connect(ui->Guy4modescene->Medium, &MyPushButton::clicked, this, &MainWindow::NormalPlay1v3);
    connect(ui->Guy4modescene->Hard, &MyPushButton::clicked, this, &MainWindow::HardPlay1v3);
}

//二人对战操作
void MainWindow::Guy2ChooseReturnToMainMenu()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->beginscene->bgm->play();/*刷夜勿用*/
    delete ui->stackedWidget->widget(2);
    delete ui->stackedWidget->widget(1);
}
void MainWindow::Guy2ChooseReturnToChooseMode()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->beginscene->bgm->play();/*刷夜勿用*/
    delete ui->stackedWidget->widget(2);
}

//四人混战操作
void MainWindow::Guy4ChooseReturnToMainMenu()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->beginscene->bgm->play();/*刷夜勿用*/
    delete ui->stackedWidget->widget(2);
    delete ui->stackedWidget->widget(1);
}
void MainWindow::Guy4ChooseReturnToChooseMode()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->beginscene->bgm->play();/*刷夜勿用*/
    delete ui->stackedWidget->widget(2);
}

//选择简单1v1模式
void MainWindow::EasyPlay1v1()
{
    ui->play1v1scene = new Play1v1(0,ui->centralwidget);
    ui->stackedWidget->addWidget(ui->play1v1scene);
    ui->stackedWidget->setCurrentIndex(3);
    //确认创建角色
    connect(ui->play1v1scene->confirm_create_player, &MyPushButton::clicked, this, &MainWindow::Play1v1ConfirmCreatePlayer);
    //点击主菜单
    connect(ui->play1v1scene->main_menu, &MyPushButton::clicked, ui->play1v1scene, &Play1v1::click_Main_menu);
    //点击退出
    connect(ui->play1v1scene->quit, &MyPushButton::clicked, this, &MainWindow::Play1v1ToBeginscene);
}
//选择中等难度1v1
void MainWindow::NormalPlay1v1(){
    ui->play1v1scene = new Play1v1(1,ui->centralwidget);
    ui->stackedWidget->addWidget(ui->play1v1scene);
    ui->stackedWidget->setCurrentIndex(3);
    //确认创建角色
    connect(ui->play1v1scene->confirm_create_player, &MyPushButton::clicked, this, &MainWindow::Play1v1ConfirmCreatePlayer);
    //点击主菜单
    connect(ui->play1v1scene->main_menu, &MyPushButton::clicked, ui->play1v1scene, &Play1v1::click_Main_menu);
    //点击退出
    connect(ui->play1v1scene->quit, &MyPushButton::clicked, this, &MainWindow::Play1v1ToBeginscene);
}
//选择困难难度1v1
void MainWindow::HardPlay1v1(){
    ui->play1v1scene = new Play1v1(2,ui->centralwidget);
    ui->stackedWidget->addWidget(ui->play1v1scene);
    ui->stackedWidget->setCurrentIndex(3);
    //确认创建角色
    connect(ui->play1v1scene->confirm_create_player, &MyPushButton::clicked, this, &MainWindow::Play1v1ConfirmCreatePlayer);
    //点击主菜单
    connect(ui->play1v1scene->main_menu, &MyPushButton::clicked, ui->play1v1scene, &Play1v1::click_Main_menu);
    //点击退出
    connect(ui->play1v1scene->quit, &MyPushButton::clicked, this, &MainWindow::Play1v1ToBeginscene);
}

//选择简单1v3模式
void MainWindow::EasyPlay1v3()
{
    ui->play1v3scene = new Play1v3(0, ui->centralwidget);
    ui->stackedWidget->addWidget(ui->play1v3scene);
    ui->stackedWidget->setCurrentIndex(3);
    qDebug()<<'*';
    //确认创建角色
    connect(ui->play1v3scene->confirm_create_player, &MyPushButton::clicked, this, &MainWindow::Play1v3ConfirmCreatePlayer);
    //点击主菜单
    connect(ui->play1v3scene->main_menu, &MyPushButton::clicked, ui->play1v3scene, &Play1v3::click_Main_menu);
    //点击退出
    connect(ui->play1v3scene->quit, &MyPushButton::clicked, this, &MainWindow::Play1v3ToBeginscene);
}
//选择中等难度1v3
void MainWindow::NormalPlay1v3(){
    ui->staytuned = new StayTuned();
    ui->staytuned->show();
    connect(ui->staytuned->sure,&MyPushButton::clicked,this,[&]{
        ui->staytuned->close();
        delete ui->staytuned;
        ui->staytuned = nullptr;
    });
}
//选择困难难度1v3
void MainWindow::HardPlay1v3(){
    ui->staytuned = new StayTuned();
    ui->staytuned->show();
    connect(ui->staytuned->sure,&MyPushButton::clicked,this,[&]{
        ui->staytuned->close();
        delete ui->staytuned;
        ui->staytuned = nullptr;
    });
}


//确认创建角色并且发牌
void MainWindow::Play1v1ConfirmCreatePlayer()
{
    if(ui->play1v1scene->lineEdit->text()!="")
    {
        QString inputText = ui->play1v1scene->lineEdit->text();
        ui->play1v1scene->ME->player_name = inputText;
        qDebug()<<"input:"<<inputText;
    }
    else
    {
        QString NullName = "Alice";
        ui->play1v1scene->ME->player_name = NullName;
        qDebug()<<"input:"<<NullName;
    }
    //把游戏进程存入文件
    QFile file("game_progress.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qDebug() << "something wrong!" ;
        return;
    }
    QDataStream out(&file);
    ui->beginscene->Totalnum += 1;
    out << ui->beginscene->Kingnum << ui->beginscene->Totalnum << ui->beginscene->Exp << ui->beginscene->Level;
    file.close();
    //
    ui->play1v1scene->ME->show();
    ui->play1v1scene->Bob->show();
    ui->play1v1scene->cardslot->show();
    ui->play1v1scene->line[0]->show();
    ui->play1v1scene->line[1]->show();
    ui->play1v1scene->line[2]->show();
    ui->play1v1scene->line[3]->show();
    ui->play1v1scene->buffer[0]->show();
    ui->play1v1scene->buffer[1]->show();

    ui->play1v1scene->lineEdit->hide();
    ui->play1v1scene->confirm_create_player->hide();
    ui->play1v1scene->title->hide();
    ui->play1v1scene->MYLabel->setText(ui->play1v1scene->ME->player_name);
    ui->play1v1scene->MYLabel->setAlignment(Qt::AlignCenter);
    ui->play1v1scene->MYLabel->setStyleSheet("font-size: 40px");
    ui->play1v1scene->BobLabel->setText("Bob");
    ui->play1v1scene->BobLabel->setAlignment(Qt::AlignCenter);
    ui->play1v1scene->BobLabel->setStyleSheet("font-size: 40px");
    ui->play1v1scene->MYHeads->setText(QString::number(ui->play1v1scene->ME->heads_num));
    ui->play1v1scene->MYHeads->setAlignment(Qt::AlignCenter);
    ui->play1v1scene->MYHeads->setStyleSheet("font-size: 40px");
    ui->play1v1scene->BobHeads->setText(QString::number(ui->play1v1scene->Bob->heads_num));
    ui->play1v1scene->BobHeads->setAlignment(Qt::AlignCenter);
    ui->play1v1scene->BobHeads->setStyleSheet("font-size: 40px");
    ui->play1v1scene->MYLabel->show();
    ui->play1v1scene->BobLabel->show();
    ui->play1v1scene->MYHeads->show();
    ui->play1v1scene->BobHeads->show();
    //初始化游戏完毕，开始发牌
    GiveCard::ThreeUnion three = GiveCard::Init1v1();
    for(int i=0; i<10; i++){
        card_pool.push_back(three.v1[i]);
    }
    for(int i=0; i<4; i++){
        card_pool.push_back(three.v3[i]);
    }
    ui->play1v1scene->ME->cards_in_hands = three.v1;
    ui->play1v1scene->Bob->cards_in_hands = three.v2;
    for(auto it : three.v1)
    {
        MyCard* tmp = new MyCard(ui->play1v1scene->cardslot,it,160,250);
        connect(tmp,&MyPushButton::clicked,this,&MainWindow::SomeCard_Clicked);
        ui->play1v1scene->cardslot->cards.push_back(tmp);
        ui->play1v1scene->cardslot->cardSlotLayout->addWidget(tmp);
    }
    for(auto it:ui->play1v1scene->cardslot->cards)
    {
        it->show();
    }
    MyCard* tmp1 = new MyCard(ui->play1v1scene->cardslot,three.v3[0],128,200);
    tmp1->is_play=1;
    ui->play1v1scene->line[0]->cards.push_back(tmp1);
    ui->play1v1scene->line[0]->cardSlotLayout->addWidget(tmp1);
    ui->play1v1scene->line[0]->lastnum = three.v3[0];
    tmp1->show();
    MyCard* tmp2 = new MyCard(ui->play1v1scene->cardslot,three.v3[1],128,200);
    tmp2->is_play=1;
    ui->play1v1scene->line[1]->cards.push_back(tmp2);
    ui->play1v1scene->line[1]->cardSlotLayout->addWidget(tmp2);
    ui->play1v1scene->line[1]->lastnum = three.v3[1];
    tmp2->show();
    MyCard* tmp3 = new MyCard(ui->play1v1scene->cardslot,three.v3[2],128,200);
    tmp3->is_play=1;
    ui->play1v1scene->line[2]->cards.push_back(tmp3);
    ui->play1v1scene->line[2]->cardSlotLayout->addWidget(tmp3);
    ui->play1v1scene->line[2]->lastnum = three.v3[2];
    tmp3->show();
    MyCard* tmp4 = new MyCard(ui->play1v1scene->cardslot,three.v3[3],128,200);
    tmp4->is_play=1;
    ui->play1v1scene->line[3]->cards.push_back(tmp4);
    ui->play1v1scene->line[3]->cardSlotLayout->addWidget(tmp4);
    ui->play1v1scene->line[3]->lastnum = three.v3[3];
    tmp4->show();
    connect(ui->play1v1scene->cancel_play_card,&MyPushButton::clicked,this,&MainWindow::Cancel_Play_Card);
    connect(ui->play1v1scene->confirm_play_card,&MyPushButton::clicked,this,&MainWindow::Confirm_Play_Card);
//    MyCard* ToRemove = qobject_cast<MyCard*>(ui->play1v1scene->cardslot->cardSlotLayout->itemAt(0)->widget());
//    ui->play1v1scene->cardslot->cardSlotLayout->removeWidget(ToRemove);
//    delete ToRemove;
    //AI mode选择
//    switch (ui->play1v1scene->whichmode)
//    {
//    case 0:
//        break;
//    case 1:
//        break;
//    case 2:
//        break;
//    }
}

//以下三个函数是出牌的关键，需要严格把握好以下几个重要的量：
//(1)明确ui->current_choose_card是哪个，便于Confirm_Play_Card出牌
//(2)每次点击一张牌后、点击另一张牌、点击取消后，相关牌的is_clicked是怎样的
void MainWindow::SomeCard_Clicked()
{
    MyCard* clickedButton = qobject_cast<MyCard*>(sender());
    if(ui->current_choose_card == nullptr)
    {
        ui->current_choose_card = clickedButton;
        ui->play1v1scene->confirm_play_card->show();
        ui->play1v1scene->cancel_play_card->show();
    }
    else
    {
        if(ui->current_choose_card == clickedButton)
        {
            ui->current_choose_card = nullptr;
            ui->play1v1scene->confirm_play_card->hide();
            ui->play1v1scene->cancel_play_card->hide();
        }
        else
        {
            ui->current_choose_card->move(ui->current_choose_card->x(),ui->current_choose_card->y() + 30);
            ui->current_choose_card->is_clicked = 0;
            ui->current_choose_card = clickedButton;
        }
    }
}
void MainWindow::Cancel_Play_Card()
{
    ui->current_choose_card->is_clicked = 0;
    ui->current_choose_card->move(ui->current_choose_card->x(),ui->current_choose_card->y()+30);
    ui->current_choose_card = nullptr;
    ui->play1v1scene->confirm_play_card->hide();
    ui->play1v1scene->cancel_play_card->hide();
}
void MainWindow::Confirm_Play_Card()
{
    int my_num = ui->current_choose_card->card_number;
    ui->play1v1scene->confirm_play_card->hide();
    ui->play1v1scene->cancel_play_card->hide();
    int pos = ui->play1v1scene->cardslot->cardSlotLayout->indexOf(ui->current_choose_card);//获取当前card的位置
    //维护
    ui->play1v1scene->cardslot->cards.erase(ui->play1v1scene->cardslot->cards.begin() + pos);
    ui->play1v1scene->cardslot->cardSlotLayout->removeWidget(ui->current_choose_card);
    delete ui->current_choose_card;
    ui->current_choose_card = nullptr;

    MyCard* mycard = new MyCard(ui->play1v1scene->buffer[0], my_num, 160, 250);
    mycard->is_play=1;
    //AI出牌
    int AI_choice = 0;

    switch (ui->play1v1scene->whichmode)
    {
    case 0:
        AI_choice = EasyAI::ChooseACard(ui->play1v1scene->Bob->cards_in_hands);
        break;
    case 1:
        AI_choice = NormAI::ChooseACard(ui->play1v1scene->Bob->cards_in_hands,
                                        my_num, //ui->current_choose_card->card_number在confirm之后就被干掉了,见348行，调用mynum就好了
                                        ui->play1v1scene->line[0]->cards,
                                        ui->play1v1scene->line[1]->cards,
                                        ui->play1v1scene->line[2]->cards,
                                        ui->play1v1scene->line[3]->cards);
        break;
    case 2:
        AI_choice = HardAI::ChooseACard(ui->play1v1scene->Bob->cards_in_hands,
                                        my_num, //ui->current_choose_card->card_number在confirm之后就被干掉了,见348行，调用mynum就好了
                                        ui->play1v1scene->line[0]->cards,
                                        ui->play1v1scene->line[1]->cards,
                                        ui->play1v1scene->line[2]->cards,
                                        ui->play1v1scene->line[3]->cards,
                                        card_pool);
        //因为此时玩家已经confirm了，因此可以通过ui->current_choose_card得到玩家的牌传进函数里，耍赖
        break;
    }
    auto itt = std::find(ui->play1v1scene->Bob->cards_in_hands.begin(),ui->play1v1scene->Bob->cards_in_hands.end(),AI_choice);
    ui->play1v1scene->Bob->cards_in_hands.erase(itt);
    MyCard* AIcard = new MyCard(ui->play1v1scene->buffer[1], AI_choice, 160, 250);
    AIcard->is_play=1;
    ui->play1v1scene->buffer[0]->cardSlotLayout->addWidget(mycard);
    ui->play1v1scene->buffer[1]->cardSlotLayout->addWidget(AIcard);
    mycard->show();
    AIcard->show(); 
    // Pause the program for the 1s to display the screen to the audience.
    QEventLoop loop;
    QTimer::singleShot(500, &loop, &QEventLoop::quit);
    loop.exec();
    mycard->hide();
    AIcard->hide();
    MyPushButton* toline[4]={ui->play1v1scene->toline1,ui->play1v1scene->toline2,
                             ui->play1v1scene->toline3,ui->play1v1scene->toline4};
    if(my_num < AI_choice)
    {
        int delta[4]={105, 105, 105, 105}, min=105, min_idx=0;
        bool check_if_min = true;                 //这张牌是否比所有槽都小
        for(int j = 0;j < 4;j++)
        {
            delta[j] = my_num - ui->play1v1scene->line[j]->lastnum;
            if(delta[j] < min && delta[j] > 0)
            {
                min = delta[j];
                min_idx = j;
            }
            if(delta[j] > 0)
            {
                check_if_min = false;
            }
        }
        if(check_if_min)
        {
            QEventLoop eventLoop;
            //替掉一个槽
            mycard->show();
            AIcard->show();
            for(int k=0;k<4;k++)
            {
                toline[k]->show();
            }
            //点不同的line按钮
            QPointer<QObject> myObject = this;
            for(int k = 0;k < 4;k++)
            {
                connect(toline[k],&QPushButton::clicked,&eventLoop,&QEventLoop::quit);
                connect(toline[k],&QPushButton::clicked,[&,myObject,k,toline,my_num]()mutable{
                    MyCard* MyCardtoslot = new MyCard(ui->play1v1scene->line[k], my_num, 128, 200);
                    MyCardtoslot->is_play=1;
                    if(myObject)
                    {
                        while (QLayoutItem* item = ui->play1v1scene->line[k]->cardSlotLayout->takeAt(0))
                        {
                            QWidget* widget = item->widget();
                            MyCard* tmpCard = qobject_cast<MyCard*>(widget);
                            // Check if the qobject_cast was successful
                            if (tmpCard)
                            {
                                ui->play1v1scene->ME->heads_num += tmpCard->heads_num;
                                delete widget;
                                widget = nullptr;
                                tmpCard = nullptr;
                            }
                            delete item;
                            item = nullptr;
                        }//将Layout中的全删掉
                        ui->play1v1scene->MYHeads->setText(QString::number(ui->play1v1scene->ME->heads_num));
                        ui->play1v1scene->line[k]->cards.clear();
                        ui->play1v1scene->line[k]->cards.push_back(MyCardtoslot);
                        ui->play1v1scene->line[k]->cardSlotLayout->addWidget(MyCardtoslot);
                        ui->play1v1scene->line[k]->lastnum = my_num;
                        for(int k=0;k<4;k++)
                        {
                            toline[k]->hide();
                            toline[k]->disconnect();
                        }
                    }

                });
            }
            eventLoop.exec();
            mycard->hide();
            AIcard->hide();
        }
        else
        {
            MyCard* MyCardtoslot = new MyCard(ui->play1v1scene->line[min_idx], my_num, 128, 200);
            MyCardtoslot->is_play=1;
            if(ui->play1v1scene->line[min_idx]->cards.size() == 5)//行满，被动吃分
            {
                while (QLayoutItem* item = ui->play1v1scene->line[min_idx]->cardSlotLayout->takeAt(0))
                {
                    QWidget* widget = item->widget();
                    MyCard* tmpCard = qobject_cast<MyCard*>(widget);
                    // Check if the qobject_cast was successful
                    if (tmpCard)
                    {
                        ui->play1v1scene->ME->heads_num += tmpCard->heads_num;
                        delete widget;
                        widget = nullptr;
                        tmpCard = nullptr;
                    }
                    delete item;
                    item = nullptr;
                }
                ui->play1v1scene->MYHeads->setText(QString::number(ui->play1v1scene->ME->heads_num));
                ui->play1v1scene->line[min_idx]->cards.clear();
                ui->play1v1scene->line[min_idx]->cards.push_back(MyCardtoslot);
                ui->play1v1scene->line[min_idx]->cardSlotLayout->addWidget(MyCardtoslot);
                ui->play1v1scene->line[min_idx]->lastnum = my_num;
//                for(int j=0;j<5;j++)
//                {
//                    ui->play1v1scene->line[min_idx]->cards[j]->hide();
//                }
            }
            else//行未满，向对应行里添牌
            {
                ui->play1v1scene->line[min_idx]->cards.push_back(MyCardtoslot);
                ui->play1v1scene->line[min_idx]->cardSlotLayout->addWidget(MyCardtoslot);
                ui->play1v1scene->line[min_idx]->lastnum = my_num;
            }
        }
        //再来给AI放牌
        int delta1[4] = {105, 105, 105, 105}, min1 = 105, min_idx1 = 0;
        bool check_if_min1 = true;                 //这张牌是否比所有槽都小
        for(int j = 0;j < 4;j++)
        {
            delta1[j] = AI_choice - ui->play1v1scene->line[j]->lastnum;
            if(delta1[j] < min1 && delta1[j] > 0)
            {
                min1 = delta1[j];
                min_idx1 = j;
            }
            if(delta1[j] > 0)
            {
                check_if_min1 = false;
            }
        }
        if(check_if_min1)
        {
            //AI选一行

            QList<MyCard*> Line[4] = {ui->play1v1scene->line[0]->cards,ui->play1v1scene->line[1]->cards,
                                       ui->play1v1scene->line[2]->cards,ui->play1v1scene->line[3]->cards};
            int k = EasyAI::ChooseARow(Line[0],Line[1],Line[2],Line[3]);
            MyCard* AICardtoslot = new MyCard(ui->play1v1scene->line[k], AI_choice, 128, 200);
            AICardtoslot->is_play=1;
            while (QLayoutItem* item = ui->play1v1scene->line[k]->cardSlotLayout->takeAt(0))
            {
                QWidget* widget = item->widget();
                MyCard* tmpCard = qobject_cast<MyCard*>(widget);
                // Check if the qobject_cast was successful
                if (tmpCard)
                {
                    ui->play1v1scene->Bob->heads_num += tmpCard->heads_num;//AI吃分
                    delete widget;
                    widget = nullptr;
                    tmpCard = nullptr;
                }
                delete item;
                item = nullptr;
            }//将Layout中的全删掉
            ui->play1v1scene->BobHeads->setText(QString::number(ui->play1v1scene->Bob->heads_num));
            ui->play1v1scene->line[k]->cards.clear();
            ui->play1v1scene->line[k]->cards.push_back(AICardtoslot);
            ui->play1v1scene->line[k]->cardSlotLayout->addWidget(AICardtoslot);
            ui->play1v1scene->line[k]->lastnum = AI_choice;
        }
        else
        {
            MyCard* AICardtoslot = new MyCard(ui->play1v1scene->line[min_idx1], AI_choice, 128, 200);
            AICardtoslot->is_play=1;
            if(ui->play1v1scene->line[min_idx1]->cards.size() == 5)//行满，被动吃分
            {
                while (QLayoutItem* item = ui->play1v1scene->line[min_idx1]->cardSlotLayout->takeAt(0))
                {
                    QWidget* widget = item->widget();
                    MyCard* tmpCard = qobject_cast<MyCard*>(widget);
                    // Check if the qobject_cast was successful
                    if (tmpCard)
                    {
                        ui->play1v1scene->Bob->heads_num += tmpCard->heads_num;
                        delete widget;
                        widget = nullptr;
                        tmpCard = nullptr;
                    }
                    delete item;
                    item = nullptr;
                }
                ui->play1v1scene->BobHeads->setText(QString::number(ui->play1v1scene->Bob->heads_num));
                ui->play1v1scene->line[min_idx1]->cards.clear();
                ui->play1v1scene->line[min_idx1]->cards.push_back(AICardtoslot);
                ui->play1v1scene->line[min_idx1]->cardSlotLayout->addWidget(AICardtoslot);
                ui->play1v1scene->line[min_idx1]->lastnum = AI_choice;
            }
            else//行未满，向对应行里添牌
            {
                ui->play1v1scene->line[min_idx1]->cards.push_back(AICardtoslot);
                ui->play1v1scene->line[min_idx1]->cardSlotLayout->addWidget(AICardtoslot);
                ui->play1v1scene->line[min_idx1]->lastnum = AI_choice;
            }
        }
    }
    else
    {
        //先给AI放牌
        int delta[4]={105, 105, 105, 105}, min = 105, min_idx=0;
        bool check_if_min = true;                 //这张牌是否比所有槽都小
        for(int j = 0;j < 4;j++)
        {
            delta[j] = AI_choice - ui->play1v1scene->line[j]->lastnum;
            if(delta[j] < min && delta[j] > 0)
            {
                min = delta[j];
                min_idx = j;
            }
            if(delta[j] > 0)
            {
                check_if_min = false;
            }
        }

        if(check_if_min)
        {
            QList<MyCard*> Line[4] = {ui->play1v1scene->line[0]->cards,ui->play1v1scene->line[1]->cards,
                                       ui->play1v1scene->line[2]->cards,ui->play1v1scene->line[3]->cards};
            int k = EasyAI::ChooseARow(Line[0],Line[1],Line[2],Line[3]);
            MyCard* AICardtoslot = new MyCard(ui->play1v1scene->line[k], AI_choice, 128, 200);
            AICardtoslot->is_play=1;
            while (QLayoutItem* item = ui->play1v1scene->line[k]->cardSlotLayout->takeAt(0))
            {
                QWidget* widget = item->widget();
                MyCard* tmpCard = qobject_cast<MyCard*>(widget);
                // Check if the qobject_cast was successful
                if (tmpCard)
                {
                    ui->play1v1scene->Bob->heads_num += tmpCard->heads_num;//AI吃分
                    delete widget;
                    widget = nullptr;
                    tmpCard = nullptr;
                }
                delete item;
                item = nullptr;
            }//将Layout中的全删掉
            ui->play1v1scene->BobHeads->setText(QString::number(ui->play1v1scene->Bob->heads_num));
            ui->play1v1scene->line[k]->cards.clear();
            ui->play1v1scene->line[k]->cards.push_back(AICardtoslot);
            ui->play1v1scene->line[k]->cardSlotLayout->addWidget(AICardtoslot);
            ui->play1v1scene->line[k]->lastnum = AI_choice;
        }
        else
        {
            MyCard* AICardtoslot = new MyCard(ui->play1v1scene->line[min_idx], AI_choice, 128, 200);
            AICardtoslot->is_play=1;
            if(ui->play1v1scene->line[min_idx]->cards.size()==5)//行满，被动吃分
            {
                while (QLayoutItem* item = ui->play1v1scene->line[min_idx]->cardSlotLayout->takeAt(0))
                {
                    QWidget* widget = item->widget();
                    MyCard* tmpCard = qobject_cast<MyCard*>(widget);
                            // Check if the qobject_cast was successful
                    if (tmpCard)
                    {
                        ui->play1v1scene->Bob->heads_num += tmpCard->heads_num;
                        delete widget;
                        widget = nullptr;
                        tmpCard = nullptr;
                    }
                    delete item;
                    item = nullptr;
                }
                ui->play1v1scene->BobHeads->setText(QString::number(ui->play1v1scene->Bob->heads_num));
                ui->play1v1scene->line[min_idx]->cards.clear();
                ui->play1v1scene->line[min_idx]->cards.push_back(AICardtoslot);
                ui->play1v1scene->line[min_idx]->cardSlotLayout->addWidget(AICardtoslot);
                ui->play1v1scene->line[min_idx]->lastnum = AI_choice;
            }
            else//行未满，向对应行里添牌
            {
                ui->play1v1scene->line[min_idx]->cards.push_back(AICardtoslot);
                ui->play1v1scene->line[min_idx]->cardSlotLayout->addWidget(AICardtoslot);
                ui->play1v1scene->line[min_idx]->lastnum = AI_choice;
            }
        }
        //再来给我放牌
        int delta1[4] = {105, 105, 105, 105}, min1 = 105, min_idx1 = 0;
        bool check_if_min1 = true;                 //这张牌是否比所有槽都小
        for(int j = 0;j < 4;j++)
        {
            delta1[j] = my_num - ui->play1v1scene->line[j]->lastnum;
            if(delta1[j] < min1 && delta1[j] > 0)
            {
                min1 = delta1[j];
                min_idx1 = j;
            }
            if(delta1[j] > 0)
            {
                check_if_min1 = false;
            }
        }
        if(check_if_min1)
        {
            //我选一行
            //替掉一个槽
            QEventLoop eventLoop;
            //替掉一个槽
            mycard->show();
            AIcard->show();
            for(int k=0;k<4;k++)
            {
                toline[k]->show();
            }
            //点不同的line按钮
            QPointer<QObject> myObject = this;
            for(int k=0;k<4;k++)
            {
                connect(toline[k],&QPushButton::clicked,&eventLoop,&QEventLoop::quit);
                connect(toline[k],&QPushButton::clicked,[&,myObject,k,toline]()mutable{
                    MyCard* MyCardtoslot = new MyCard(ui->play1v1scene->line[k], my_num, 128, 200);
                    MyCardtoslot->is_play=1;
                    if(myObject)
                    {
                        while (QLayoutItem* item = ui->play1v1scene->line[min_idx]->cardSlotLayout->takeAt(0))
                        {
                            QWidget* widget = item->widget();
                            MyCard* tmpCard = qobject_cast<MyCard*>(widget);
                            // Check if the qobject_cast was successful
                            if (tmpCard)
                            {
                                ui->play1v1scene->ME->heads_num += tmpCard->heads_num;//统计牛头数
                                delete widget;
                                widget = nullptr;
                                tmpCard = nullptr;
                            }
                            delete item;
                            item = nullptr;
                        }//将Layout中的全删掉
                        ui->play1v1scene->MYHeads->setText(QString::number(ui->play1v1scene->ME->heads_num));
                        ui->play1v1scene->line[min_idx]->cards.clear();
                        ui->play1v1scene->line[k]->cards.push_back(MyCardtoslot);
                        ui->play1v1scene->line[k]->cardSlotLayout->addWidget(MyCardtoslot);
                        ui->play1v1scene->line[k]->lastnum = my_num;//维持每行最后一数
                        for(int k=0;k<4;k++)
                        {
                            toline[k]->hide();
                            toline[k]->disconnect();
                        }
                    }
                });
            }
            eventLoop.exec();
            mycard->hide();
            AIcard->hide();
        }
        else
        {
            MyCard* MyCardtoslot = new MyCard(ui->play1v1scene->line[min_idx1], my_num, 128, 200);
            MyCardtoslot->is_play=1;
            if(ui->play1v1scene->line[min_idx1]->cards.size() == 5)//行满，被动吃分
            {
                while (QLayoutItem* item = ui->play1v1scene->line[min_idx1]->cardSlotLayout->takeAt(0))
                {
                    QWidget* widget = item->widget();
                    MyCard* tmpCard = qobject_cast<MyCard*>(widget);
                            // Check if the qobject_cast was successful
                    if (tmpCard)
                    {
                        ui->play1v1scene->ME->heads_num += tmpCard->heads_num;
                        delete widget;
                        widget = nullptr;
                        tmpCard = nullptr;
                    }
                    delete item;
                    item = nullptr;
                }
                ui->play1v1scene->MYHeads->setText(QString::number(ui->play1v1scene->ME->heads_num));
                ui->play1v1scene->line[min_idx1]->cards.clear();
                ui->play1v1scene->line[min_idx1]->cards.push_back(MyCardtoslot);
                ui->play1v1scene->line[min_idx1]->cardSlotLayout->addWidget(MyCardtoslot);
                ui->play1v1scene->line[min_idx1]->lastnum = my_num;
            }
            else//行未满，向对应行里添牌
            {
                ui->play1v1scene->line[min_idx1]->cards.push_back(MyCardtoslot);
                ui->play1v1scene->line[min_idx1]->cardSlotLayout->addWidget(MyCardtoslot);
                ui->play1v1scene->line[min_idx1]->lastnum = my_num;
            }
        }
    }
    ui->play1v1scene->buffer[0]->cardSlotLayout->removeWidget(mycard);
    ui->play1v1scene->buffer[1]->cardSlotLayout->removeWidget(AIcard);
    delete mycard;
    delete AIcard;
    if(ui->play1v1scene->cardslot->cards.size() == 0 )
        MainWindow::finish_a_game();
}

void MainWindow::finish_a_game()//我优化了一下这个函数，使之效率更高
{
    qDebug()<<"Hooray!";
    for(int i = 0 ; i < 4 ; i++)
        for(int j = 0 ; j < ui->play1v1scene->line[i]->cards.size() ; j++)
            ui->play1v1scene->line[i]->cards[j]->hide();
    ui->play1v1scene->cardslot->setFixedSize(1, 1);
    for(int i=0;i<4;i++)
        ui->play1v1scene->line[i]->setFixedSize(1, 1);
    if(ui->play1v1scene->ME->heads_num < ui->play1v1scene->Bob->heads_num)
    {
        ui->play1v1scene->FinishImage = new MyPushButton(this, 0, ":/res/Res/vic.png", ":/res/Res/vic.png");
        //把游戏进程存入文件
        QFile file("game_progress.txt");
        if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
            qDebug() << "something wrong!" ;
            return;
        }
        QDataStream out(&file);
        ui->beginscene->Kingnum += 1;
        ui->beginscene->Exp += 2 * (100 - (ui->play1v1scene->ME->heads_num - ui->play1v1scene->Bob->heads_num));
        if(ui->beginscene->Exp >= 1000){
            ui->beginscene->Level += ui->beginscene->Exp / 1000;
            ui->beginscene->Exp %= 1000;
        }
        out << ui->beginscene->Kingnum << ui->beginscene->Totalnum << ui->beginscene->Exp << ui->beginscene->Level;
        file.close();
        //
    }
    else if(ui->play1v1scene->ME->heads_num > ui->play1v1scene->Bob->heads_num)
    {
        ui->play1v1scene->FinishImage = new MyPushButton(this, 0, ":/res/Res/losePic.png", ":/res/Res/losePic.png");
        //把游戏进程存入文件
        QFile file("game_progress.txt");
        if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
            qDebug() << "something wrong!" ;
            return;
        }
        QDataStream out(&file);
        ui->beginscene->Exp += 1 * (60 - (ui->play1v1scene->ME->heads_num - ui->play1v1scene->Bob->heads_num));
        if(ui->beginscene->Exp >= 1000){
            ui->beginscene->Level += ui->beginscene->Exp / 1000;
            ui->beginscene->Exp %= 1000;
        }
        out << ui->beginscene->Kingnum << ui->beginscene->Totalnum << ui->beginscene->Exp << ui->beginscene->Level;
        file.close();
        //
    }
    else
    {
        ui->play1v1scene->FinishImage = new MyPushButton(this, 0, ":/res/Res/pingjuPic.png", ":/res/Res/pingjuPic.png");
        //把游戏进程存入文件
        QFile file("game_progress.txt");
        if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
            qDebug() << "something wrong!" ;
            return;
        }
        QDataStream out(&file);
        ui->beginscene->Exp += 1 * (80 - (ui->play1v1scene->ME->heads_num - ui->play1v1scene->Bob->heads_num));
        if(ui->beginscene->Exp >= 1000){
            ui->beginscene->Level += ui->beginscene->Exp / 1000;
            ui->beginscene->Exp %= 1000;
        }
        out << ui->beginscene->Kingnum << ui->beginscene->Totalnum << ui->beginscene->Exp << ui->beginscene->Level;
        file.close();
        //
    }
    ui->play1v1scene->FinishImage->setFixedSize(800, 600);
    ui->play1v1scene->FinishImage->move(400, 100);
    ui->play1v1scene->FinishImage->show();
    ui->play1v1scene->finish_button->show();
    connect(ui->play1v1scene->finish_button, &MyPushButton::clicked, this, &MainWindow::Play1v1ToBeginscene);
}

//确认创建角色并且发牌
void MainWindow::Play1v3ConfirmCreatePlayer()
{

    if(ui->play1v3scene->lineEdit->text()!="")
    {
        QString inputText = ui->play1v3scene->lineEdit->text();
        ui->play1v3scene->ME->player_name=inputText;
        qDebug()<<"input:"<<inputText;
    }
    else
    {
        QString NullName = "Alice";
        ui->play1v3scene->ME->player_name=NullName;
        qDebug()<<"input:"<<NullName;
    }
    //把游戏进程存入文件
    QFile file("game_progress.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qDebug() << "something wrong!" ;
        return;
    }
    QDataStream out(&file);
    ui->beginscene->Totalnum += 1;
    out << ui->beginscene->Kingnum << ui->beginscene->Totalnum << ui->beginscene->Exp << ui->beginscene->Level;
    file.close();
    //
    ui->play1v3scene->ME->show();
    ui->play1v3scene->Bob->show();
    ui->play1v3scene->Carol->show();
    ui->play1v3scene->Dave->show();
    ui->play1v3scene->cardslot->show();
    ui->play1v3scene->line[0]->show();
    ui->play1v3scene->line[1]->show();
    ui->play1v3scene->line[2]->show();
    ui->play1v3scene->line[3]->show();
    ui->play1v3scene->buffer[0]->show();
    ui->play1v3scene->buffer[1]->show();
    ui->play1v3scene->buffer[2]->show();
    ui->play1v3scene->buffer[3]->show();

    ui->play1v3scene->lineEdit->hide();
    ui->play1v3scene->confirm_create_player->hide();
    ui->play1v3scene->title->hide();

    ui->play1v3scene->MYLabel->setText(ui->play1v3scene->ME->player_name);
    ui->play1v3scene->MYLabel->setAlignment(Qt::AlignCenter);
    ui->play1v3scene->MYLabel->setStyleSheet("font-size: 40px");

    ui->play1v3scene->BobLabel->setText("Bob");
    ui->play1v3scene->BobLabel->setAlignment(Qt::AlignCenter);
    ui->play1v3scene->BobLabel->setStyleSheet("font-size: 40px");

    ui->play1v3scene->CarolLabel->setText("Carol");
    ui->play1v3scene->CarolLabel->setAlignment(Qt::AlignCenter);
    ui->play1v3scene->CarolLabel->setStyleSheet("font-size: 40px");

    ui->play1v3scene->DaveLabel->setText("Dave");
    ui->play1v3scene->DaveLabel->setAlignment(Qt::AlignCenter);
    ui->play1v3scene->DaveLabel->setStyleSheet("font-size: 40px");

    ui->play1v3scene->MYHeads->setText(QString::number(ui->play1v3scene->ME->heads_num));
    ui->play1v3scene->MYHeads->setAlignment(Qt::AlignCenter);
    ui->play1v3scene->MYHeads->setStyleSheet("font-size: 40px");

    ui->play1v3scene->BobHeads->setText(QString::number(ui->play1v3scene->Bob->heads_num));
    ui->play1v3scene->BobHeads->setAlignment(Qt::AlignCenter);
    ui->play1v3scene->BobHeads->setStyleSheet("font-size: 40px");

    ui->play1v3scene->CarolHeads->setText(QString::number(ui->play1v3scene->Carol->heads_num));
    ui->play1v3scene->CarolHeads->setAlignment(Qt::AlignCenter);
    ui->play1v3scene->CarolHeads->setStyleSheet("font-size: 40px");

    ui->play1v3scene->DaveHeads->setText(QString::number(ui->play1v3scene->Dave->heads_num));
    ui->play1v3scene->DaveHeads->setAlignment(Qt::AlignCenter);
    ui->play1v3scene->DaveHeads->setStyleSheet("font-size: 40px");

    ui->play1v3scene->MYLabel->show();
    ui->play1v3scene->BobLabel->show();
    ui->play1v3scene->CarolLabel->show();
    ui->play1v3scene->DaveLabel->show();

    ui->play1v3scene->MYHeads->show();
    ui->play1v3scene->BobHeads->show();
    ui->play1v3scene->CarolHeads->show();
    ui->play1v3scene->DaveHeads->show();
    //初始化游戏完毕，开始发牌
    GiveCard::FiveUnion five = GiveCard::Init1v3();
    ui->play1v3scene->ME->cards_in_hands = five.v1;
    ui->play1v3scene->Bob->cards_in_hands = five.v2;
    ui->play1v3scene->Carol->cards_in_hands = five.v3;
    ui->play1v3scene->Dave->cards_in_hands = five.v4;
    for(auto it : five.v1)
    {
        MyCard* tmp = new MyCard(ui->play1v3scene->cardslot,it,160,250);
        connect(tmp,&MyPushButton::clicked,this,&MainWindow::SomeCard_Clicked_3);
        ui->play1v3scene->cardslot->cards.push_back(tmp);
        ui->play1v3scene->cardslot->cardSlotLayout->addWidget(tmp);
    }
    for(auto it:ui->play1v3scene->cardslot->cards)
    {
        it->show();
    }
    MyCard* tmp1 = new MyCard(ui->play1v3scene->cardslot,five.v5[0],128,200);
    tmp1->is_play=1;
    ui->play1v3scene->line[0]->cards.push_back(tmp1);
    ui->play1v3scene->line[0]->cardSlotLayout->addWidget(tmp1);
    ui->play1v3scene->line[0]->lastnum = five.v5[0];
    tmp1->show();
    MyCard* tmp2 = new MyCard(ui->play1v3scene->cardslot,five.v5[1],128,200);
    tmp2->is_play=1;
    ui->play1v3scene->line[1]->cards.push_back(tmp2);
    ui->play1v3scene->line[1]->cardSlotLayout->addWidget(tmp2);
    ui->play1v3scene->line[1]->lastnum = five.v5[1];
    tmp2->show();
    MyCard* tmp3 = new MyCard(ui->play1v3scene->cardslot,five.v5[2],128,200);
    tmp3->is_play=1;
    ui->play1v3scene->line[2]->cards.push_back(tmp3);
    ui->play1v3scene->line[2]->cardSlotLayout->addWidget(tmp3);
    ui->play1v3scene->line[2]->lastnum = five.v5[2];
    tmp3->show();
    MyCard* tmp4 = new MyCard(ui->play1v3scene->cardslot,five.v5[3],128,200);
    tmp4->is_play=1;
    ui->play1v3scene->line[3]->cards.push_back(tmp4);
    ui->play1v3scene->line[3]->cardSlotLayout->addWidget(tmp4);
    ui->play1v3scene->line[3]->lastnum = five.v5[3];
    tmp4->show();
    connect(ui->play1v3scene->cancel_play_card,&MyPushButton::clicked,this,&MainWindow::Cancel_Play_Card_3);
    connect(ui->play1v3scene->confirm_play_card,&MyPushButton::clicked,this,&MainWindow::Confirm_Play_Card_3);
}
void MainWindow::SomeCard_Clicked_3()
{
    MyCard* clickedButton = qobject_cast<MyCard*>(sender());
    if(ui->current_choose_card == nullptr)
    {
        ui->current_choose_card = clickedButton;
        ui->play1v3scene->confirm_play_card->show();
        ui->play1v3scene->cancel_play_card->show();
    }
    else
    {
        if(ui->current_choose_card == clickedButton)
        {
            ui->current_choose_card = nullptr;
            ui->play1v3scene->confirm_play_card->hide();
            ui->play1v3scene->cancel_play_card->hide();
        }
        else
        {
            ui->current_choose_card->move(ui->current_choose_card->x(),ui->current_choose_card->y() + 30);
            ui->current_choose_card->is_clicked = 0;
            ui->current_choose_card = clickedButton;
        }
    }
}
void MainWindow::Cancel_Play_Card_3()
{
    ui->current_choose_card->is_clicked = 0;
    ui->current_choose_card->move(ui->current_choose_card->x(),ui->current_choose_card->y()+30);
    ui->current_choose_card = nullptr;
    ui->play1v3scene->confirm_play_card->hide();
    ui->play1v3scene->cancel_play_card->hide();
}
void MainWindow::Confirm_Play_Card_3()
{
    int my_num = ui->current_choose_card->card_number;
    ui->play1v3scene->confirm_play_card->hide();
    ui->play1v3scene->cancel_play_card->hide();
    int pos = ui->play1v3scene->cardslot->cardSlotLayout->indexOf(ui->current_choose_card);//获取当前card的位置
    //维护
    ui->play1v3scene->cardslot->cards.erase(ui->play1v3scene->cardslot->cards.begin() + pos);
    ui->play1v3scene->cardslot->cardSlotLayout->removeWidget(ui->current_choose_card);
    delete ui->current_choose_card;
    ui->current_choose_card = nullptr;

    MyCard* mycard = new MyCard(ui->play1v3scene->buffer[0], my_num, 160, 250);
    mycard->is_play=1;

    //AI出牌
    int Bob_choice = 0, Carol_choice = 0, Dave_choice = 0;

    switch(ui->play1v3scene->whichmode)
    {
    case 0:
        Bob_choice = EasyAI::ChooseACard(ui->play1v3scene->Bob->cards_in_hands);
        Carol_choice = EasyAI::ChooseACard(ui->play1v3scene->Carol->cards_in_hands);
        Dave_choice = EasyAI::ChooseACard(ui->play1v3scene->Dave->cards_in_hands);
        break;
    case 1:
        break;
    case 2:
        break;
    }
    auto itt_bob = std::find(ui->play1v3scene->Bob->cards_in_hands.begin(),ui->play1v3scene->Bob->cards_in_hands.end(),Bob_choice);
    auto itt_carol = std::find(ui->play1v3scene->Carol->cards_in_hands.begin(),ui->play1v3scene->Carol->cards_in_hands.end(),Carol_choice);
    auto itt_dave = std::find(ui->play1v3scene->Dave->cards_in_hands.begin(),ui->play1v3scene->Dave->cards_in_hands.end(),Dave_choice);
    ui->play1v3scene->Bob->cards_in_hands.erase(itt_bob);
    ui->play1v3scene->Carol->cards_in_hands.erase(itt_carol);
    ui->play1v3scene->Dave->cards_in_hands.erase(itt_dave);
    MyCard* Bobcard = new MyCard(ui->play1v3scene->buffer[1], Bob_choice, 160, 250);
    MyCard* Carolcard = new MyCard(ui->play1v3scene->buffer[2], Carol_choice, 160, 250);
    MyCard* Davecard = new MyCard(ui->play1v3scene->buffer[3], Dave_choice, 160, 250);

    ui->play1v3scene->buffer[0]->cardSlotLayout->addWidget(mycard);
    ui->play1v3scene->buffer[1]->cardSlotLayout->addWidget(Bobcard);
    ui->play1v3scene->buffer[2]->cardSlotLayout->addWidget(Carolcard);
    ui->play1v3scene->buffer[3]->cardSlotLayout->addWidget(Davecard);
    mycard->show();
    Bobcard->show();
    Carolcard->show();
    Davecard->show();
    //Pause
    QEventLoop loop;
    QTimer::singleShot(500, &loop, &QEventLoop::quit);
    loop.exec();
    mycard->hide();
    Bobcard->hide();
    Carolcard->hide();
    Davecard->hide();
    MyPushButton* toline[4]={ui->play1v3scene->toline1,ui->play1v3scene->toline2,
                             ui->play1v3scene->toline3,ui->play1v3scene->toline4};
    //定义结构体来决定谁先放牌，放在哪里
    struct Candidate{
        int idx;
        int card_num;
        MyCard* card;
    }candi[4];
    candi[0].idx = 0;  //0号指玩家
    candi[0].card_num = my_num;
    candi[0].card = mycard;
    candi[1].idx = 1;  //1~3号指AI
    candi[1].card_num = Bob_choice;
    candi[1].card = Bobcard;
    candi[2].idx = 2;
    candi[2].card_num = Carol_choice;
    candi[2].card = Carolcard;
    candi[3].idx = 3;
    candi[3].card_num = Dave_choice;
    candi[3].card = Davecard;
    //接下来按照card_num排序
    qsort(candi, 4, sizeof(Candidate), [](const void* a, const void* b) {
        const Candidate* candidateA = static_cast<const Candidate*>(a);
        const Candidate* candidateB = static_cast<const Candidate*>(b);

        if (candidateA->card_num < candidateB->card_num)
            return -1;
        else if (candidateA->card_num > candidateB->card_num)
            return 1;
        else
            return 0;
    });
    //放牌
    for(int i=0; i<4; i++){
        int delta[4]={105, 105, 105, 105}, min=105, min_idx=0;
        bool check_if_min = true;                 //这张牌是否比所有槽都小
        for(int j = 0;j < 4;j++)
        {
            delta[j] = candi[i].card_num - ui->play1v3scene->line[j]->lastnum;
            if(delta[j] < min && delta[j] > 0)
            {
                min = delta[j];
                min_idx = j;
            }
            if(delta[j] > 0)
            {
                check_if_min = false;
            }
        }
        if(candi[i].idx == 0){
            if(check_if_min){
                QEventLoop eventLoop;
                //替掉一个槽
                mycard->show();
                Bobcard->show();
                Carolcard->show();
                Davecard->show();
                for(int k=0;k<4;k++)
                {
                    toline[k]->show();
                }
                //点不同的line按钮
                QPointer<QObject> myObject = this;
                for(int k = 0;k < 4;k++)
                {
                    connect(toline[k],&QPushButton::clicked,&eventLoop,&QEventLoop::quit);
                    connect(toline[k],&QPushButton::clicked,[&,myObject,k,toline,my_num]()mutable{
                        MyCard* MyCardtoslot = new MyCard(ui->play1v3scene->line[k], my_num, 128, 200);
                        MyCardtoslot->is_play=1;
                        if(myObject)
                        {
                            while (QLayoutItem* item = ui->play1v3scene->line[k]->cardSlotLayout->takeAt(0))
                            {
                                QWidget* widget = item->widget();
                                MyCard* tmpCard = qobject_cast<MyCard*>(widget);
                                // Check if the qobject_cast was successful
                                if (tmpCard)
                                {
                                    ui->play1v3scene->ME->heads_num += tmpCard->heads_num;
                                    delete widget;
                                    widget = nullptr;
                                    tmpCard = nullptr;
                                }
                                delete item;
                                item = nullptr;
                            }//将Layout中的全删掉
                            ui->play1v3scene->MYHeads->setText(QString::number(ui->play1v3scene->ME->heads_num));
                            ui->play1v3scene->line[k]->cards.clear();
                            ui->play1v3scene->line[k]->cards.push_back(MyCardtoslot);
                            ui->play1v3scene->line[k]->cardSlotLayout->addWidget(MyCardtoslot);
                            ui->play1v3scene->line[k]->lastnum = my_num;
                            for(int k=0;k<4;k++)
                            {
                                toline[k]->hide();
                                toline[k]->disconnect();
                            }
                        }

                    });
                }
                eventLoop.exec();
                mycard->hide();
                Bobcard->hide();
                Carolcard->hide();
                Davecard->hide();
            }
            else{
                MyCard* MyCardtoslot = new MyCard(ui->play1v3scene->line[min_idx], my_num, 128, 200);
                MyCardtoslot->is_play=1;
                if(ui->play1v3scene->line[min_idx]->cards.size() == 5)//行满，被动吃分
                {
                    while (QLayoutItem* item = ui->play1v3scene->line[min_idx]->cardSlotLayout->takeAt(0))
                    {
                        QWidget* widget = item->widget();
                        MyCard* tmpCard = qobject_cast<MyCard*>(widget);
                        // Check if the qobject_cast was successful
                        if (tmpCard)
                        {
                            ui->play1v3scene->ME->heads_num += tmpCard->heads_num;
                            delete widget;
                            widget = nullptr;
                            tmpCard = nullptr;
                        }
                        delete item;
                        item = nullptr;
                    }
                    ui->play1v3scene->MYHeads->setText(QString::number(ui->play1v3scene->ME->heads_num));
                    ui->play1v3scene->line[min_idx]->cards.clear();
                    ui->play1v3scene->line[min_idx]->cards.push_back(MyCardtoslot);
                    ui->play1v3scene->line[min_idx]->cardSlotLayout->addWidget(MyCardtoslot);
                    ui->play1v3scene->line[min_idx]->lastnum = my_num;
    //                for(int j=0;j<5;j++)
    //                {
    //                    ui->play1v1scene->line[min_idx]->cards[j]->hide();
    //                }
                }
                else//行未满，向对应行里添牌
                {
                    ui->play1v3scene->line[min_idx]->cards.push_back(MyCardtoslot);
                    ui->play1v3scene->line[min_idx]->cardSlotLayout->addWidget(MyCardtoslot);
                    ui->play1v3scene->line[min_idx]->lastnum = my_num;
                }
            }
        }
        else{
            if(check_if_min)
            {
                //AI选一行
                int AI_choice = 0;
                QList<MyCard*> Line[4] = {ui->play1v3scene->line[0]->cards,ui->play1v3scene->line[1]->cards,
                                           ui->play1v3scene->line[2]->cards,ui->play1v3scene->line[3]->cards};
                int k = EasyAI::ChooseARow(Line[0],Line[1],Line[2],Line[3]);
                if(candi[i].idx == 1){
                    AI_choice = Bob_choice;
                }
                else if(candi[i].idx == 2){
                    AI_choice = Carol_choice;
                }
                else if(candi[i].idx == 3){
                    AI_choice = Dave_choice;
                }
                MyCard* AICardtoslot = new MyCard(ui->play1v3scene->line[k], AI_choice, 128, 200);
                AICardtoslot->is_play=1;
                while (QLayoutItem* item = ui->play1v3scene->line[k]->cardSlotLayout->takeAt(0))
                {
                    QWidget* widget = item->widget();
                    MyCard* tmpCard = qobject_cast<MyCard*>(widget);
                    // Check if the qobject_cast was successful
                    if (tmpCard)
                    {
                        if(candi[i].idx == 1) ui->play1v3scene->Bob->heads_num += tmpCard->heads_num;//AI吃分
                        else if(candi[i].idx == 2) ui->play1v3scene->Carol->heads_num += tmpCard->heads_num;
                        else if(candi[i].idx == 3) ui->play1v3scene->Dave->heads_num += tmpCard->heads_num;
                        delete widget;
                        widget = nullptr;
                        tmpCard = nullptr;
                    }
                    delete item;
                    item = nullptr;
                }//将Layout中的全删掉
                if(candi[i].idx == 1) ui->play1v3scene->BobHeads->setText(QString::number(ui->play1v3scene->Bob->heads_num));
                else if(candi[i].idx == 2) ui->play1v3scene->CarolHeads->setText(QString::number(ui->play1v3scene->Carol->heads_num));
                else if(candi[i].idx == 3) ui->play1v3scene->DaveHeads->setText(QString::number(ui->play1v3scene->Dave->heads_num));
                ui->play1v3scene->line[k]->cards.clear();
                ui->play1v3scene->line[k]->cards.push_back(AICardtoslot);
                ui->play1v3scene->line[k]->cardSlotLayout->addWidget(AICardtoslot);
                ui->play1v3scene->line[k]->lastnum = AI_choice;
            }
            else
            {
                int AI_choice = 0;
                if(candi[i].idx == 1){
                    AI_choice = Bob_choice;
                }
                else if(candi[i].idx == 2){
                    AI_choice = Carol_choice;
                }
                else if(candi[i].idx == 3){
                    AI_choice = Dave_choice;
                }
                MyCard* AICardtoslot = new MyCard(ui->play1v3scene->line[min_idx], AI_choice, 128, 200);
                AICardtoslot->is_play=1;
                if(ui->play1v3scene->line[min_idx]->cards.size() == 5)//行满，被动吃分
                {
                    while (QLayoutItem* item = ui->play1v3scene->line[min_idx]->cardSlotLayout->takeAt(0))
                    {
                        QWidget* widget = item->widget();
                        MyCard* tmpCard = qobject_cast<MyCard*>(widget);
                        // Check if the qobject_cast was successful
                        if (tmpCard)
                        {
                            if(candi[i].idx == 1) ui->play1v3scene->Bob->heads_num += tmpCard->heads_num;//AI吃分
                            else if(candi[i].idx == 2) ui->play1v3scene->Carol->heads_num += tmpCard->heads_num;
                            else if(candi[i].idx == 3) ui->play1v3scene->Dave->heads_num += tmpCard->heads_num;
                            delete widget;
                            widget = nullptr;
                            tmpCard = nullptr;
                        }
                        delete item;
                        item = nullptr;
                    }
                    if(candi[i].idx == 1) ui->play1v3scene->BobHeads->setText(QString::number(ui->play1v3scene->Bob->heads_num));
                    else if(candi[i].idx == 2) ui->play1v3scene->CarolHeads->setText(QString::number(ui->play1v3scene->Carol->heads_num));
                    else if(candi[i].idx == 3) ui->play1v3scene->DaveHeads->setText(QString::number(ui->play1v3scene->Dave->heads_num));
                    ui->play1v3scene->line[min_idx]->cards.clear();
                    ui->play1v3scene->line[min_idx]->cards.push_back(AICardtoslot);
                    ui->play1v3scene->line[min_idx]->cardSlotLayout->addWidget(AICardtoslot);
                    ui->play1v3scene->line[min_idx]->lastnum = AI_choice;
                }
                else//行未满，向对应行里添牌
                {
                    ui->play1v3scene->line[min_idx]->cards.push_back(AICardtoslot);
                    ui->play1v3scene->line[min_idx]->cardSlotLayout->addWidget(AICardtoslot);
                    ui->play1v3scene->line[min_idx]->lastnum = AI_choice;
                }
            }
        }
    }
    ui->play1v3scene->buffer[0]->cardSlotLayout->removeWidget(mycard);
    ui->play1v3scene->buffer[1]->cardSlotLayout->removeWidget(Bobcard);
    ui->play1v3scene->buffer[2]->cardSlotLayout->removeWidget(Carolcard);
    ui->play1v3scene->buffer[3]->cardSlotLayout->removeWidget(Davecard);
    delete mycard;
    delete Bobcard;
    delete Carolcard;
    delete Davecard;
    if(ui->play1v3scene->cardslot->cards.size() == 0 )
        MainWindow::finish_1v3_game();
}

void MainWindow::finish_1v3_game()
{
    for(int i = 0 ; i < 4 ; i++)
        for(int j = 0 ; j < ui->play1v3scene->line[i]->cards.size() ; j++)
            ui->play1v3scene->line[i]->cards[j]->hide();
    ui->play1v3scene->cardslot->setFixedSize(1, 1);
    for(int i=0;i<4;i++)
        ui->play1v3scene->line[i]->setFixedSize(1, 1);
    struct Candidate{
        QString name;
        int heads;
        //QString avatar; //可以将图片加上
    }candi[4];
    candi[0].name = ui->play1v3scene->ME->player_name;
    candi[0].heads = ui->play1v3scene->ME->heads_num;
    //candi[0].avatar = ui->play1v3scene->ME->avatar_PATH;
    candi[1].name = ui->play1v3scene->Bob->player_name;
    candi[1].heads = ui->play1v3scene->Bob->heads_num;
    //candi[0].avatar = ui->play1v3scene->Bob->avatar_PATH;
    candi[2].name = ui->play1v3scene->Carol->player_name;
    candi[2].heads = ui->play1v3scene->Carol->heads_num;
    //candi[0].avatar = ui->play1v3scene->Carol->avatar_PATH;
    candi[3].name = ui->play1v3scene->Dave->player_name;
    candi[3].heads = ui->play1v3scene->Dave->heads_num;
    //candi[0].avatar = ui->play1v3scene->Dave->avatar_PATH;
    qsort(candi, 4, sizeof(Candidate), [](const void* a, const void* b) {
        const Candidate* candidateA = static_cast<const Candidate*>(a);
        const Candidate* candidateB = static_cast<const Candidate*>(b);

        if (candidateA->heads < candidateB->heads)
            return -1;
        else if (candidateA->heads > candidateB->heads)
            return 1;
        else
            return 0;
    });

    //找到玩家名次，方便加经验
    int pc_rank = 1;
    for(size_t j=0; j<4; j++){
        if(candi[j].name == ui->play1v3scene->ME->player_name){
            pc_rank = j+1;
        }
    }
    //加经验
    if(pc_rank == 1){
        //把游戏进程存入文件
        QFile file("game_progress.txt");
        if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
            qDebug() << "something wrong!" ;
            return;
        }
        QDataStream out(&file);
        ui->beginscene->Kingnum += 1;
        ui->beginscene->Exp += 5 * (100 - ui->play1v3scene->ME->heads_num
                                    + (ui->play1v3scene->Bob->heads_num + ui->play1v3scene->Carol->heads_num
                                    + ui->play1v3scene->Dave->heads_num));
        if(ui->beginscene->Exp >= 1000){
            ui->beginscene->Level += ui->beginscene->Exp / 1000;
            ui->beginscene->Exp %= 1000;
        }
        out << ui->beginscene->Kingnum << ui->beginscene->Totalnum << ui->beginscene->Exp << ui->beginscene->Level;
        file.close();
        //
    }
    else{
        //把游戏进程存入文件
        QFile file("game_progress.txt");
        if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
            qDebug() << "something wrong!" ;
            return;
        }
        QDataStream out(&file);
        ui->beginscene->Exp += (5 - pc_rank) * (100 - ui->play1v3scene->ME->heads_num
                                                + (ui->play1v3scene->Bob->heads_num + ui->play1v3scene->Carol->heads_num
                                                + ui->play1v3scene->Dave->heads_num));
        if(ui->beginscene->Exp >= 1000){
            ui->beginscene->Level += ui->beginscene->Exp / 1000;
            ui->beginscene->Exp %= 1000;
        }
        out << ui->beginscene->Kingnum << ui->beginscene->Totalnum << ui->beginscene->Exp << ui->beginscene->Level;
        file.close();
        //
    }

    ui->gradelist = new GradeList();
    ui->gradelist->show();
    ui->gradelist->title->setText("成绩单");
    ui->gradelist->title->show();
    for(int i = 0;i < 4;i++)
    {
        ui->gradelist->Player[i]->setText(QString(candi[i].name));
        ui->gradelist->Player[i]->setFixedSize(150,80);
        ui->gradelist->Player[i]->setAlignment(Qt::AlignCenter);
        ui->gradelist->Player[i]->move(300,100+i*80);
        ui->gradelist->Player[i]->setStyleSheet("font-size: 40px");
        ui->gradelist->Player[i]->show();
        ui->gradelist->Score[i]->setText(QString::number(candi[i].heads));
        ui->gradelist->Score[i]->setFixedSize(150,80);
        ui->gradelist->Score[i]->setAlignment(Qt::AlignCenter);
        ui->gradelist->Score[i]->move(650,100+i*80);
        ui->gradelist->Score[i]->setStyleSheet("font-size: 40px");
        ui->gradelist->Score[i]->show();
    }
    connect(ui->gradelist->sure, &QPushButton::clicked, this,[&]{
        ui->gradelist->close();
        delete ui->gradelist;
        ui->gradelist = nullptr;
        MainWindow::Play1v3ToBeginscene();
    });
}

void MainWindow::Play1v1ToBeginscene()
{
    ui->stackedWidget->setCurrentIndex(0);
    if(ui->play1v1scene->FinishImage != nullptr)
        ui->play1v1scene->FinishImage->hide();
//    ui->beginscene->bgm->play();/*刷夜勿用*/
    delete ui->stackedWidget->widget(3);
    delete ui->stackedWidget->widget(2);
    delete ui->stackedWidget->widget(1);
    if(ui->name_label!=NULL)
    {
        delete ui->name_label;
        ui->name_label=NULL;
    }
}
void MainWindow::Play1v3ToBeginscene(){
    ui->stackedWidget->setCurrentIndex(0);
//    ui->beginscene->bgm->play();/*刷夜勿用*/
    delete ui->stackedWidget->widget(3);
    delete ui->stackedWidget->widget(2);
    delete ui->stackedWidget->widget(1);
    if(ui->name_label!=NULL)
    {
        delete ui->name_label;
        ui->name_label=NULL;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
