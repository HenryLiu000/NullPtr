#include "beginscene.h"
#include <QDebug>
BeginScene::BeginScene(QWidget *parent):QWidget(parent){
    bgm = new QSound(":/res/Res/bgm01.wav");
    bgm->setLoops(-1);
    bgm->play();/*刷夜不放*/
    start = new MyPushButton(this, 0, ":/button/button04.png", ":/button/button04.png");
    setting = new MyPushButton(this, 0, ":/button/button03.png", ":/button/button03.png");
    rule = new MyPushButton(this, 0, ":/button/button12.png", ":/button/button12.png");
    start->resize(300,100);
    start->move(650,900);
    setting->resize(300,100);
    setting->move(200,900);
    rule->resize(300,100);
    rule->move(1100,900);
    start->setStyleSheet("font-size: 40px");
    setting->setStyleSheet("font-size: 40px");
    rule->setStyleSheet("font-size: 40px");
    Quitgame = new MyPushButton(this, 0, ":/button/button10.png", ":/button/button10.png");
    Quitgame->resize(200,100);
    Quitgame->move(1365,0);
    Quitgame->setStyleSheet("font-size: 30px");
    //导入储存信息
    file = new QFile("game_progress.txt");
    if (!file->open(QIODevice::ReadOnly)) {
        qDebug() << "something wrong!" ;
    }
    QDataStream in(file);
    in >> Kingnum >> Totalnum >> Exp >> Level;
    file->close();
    info = new QLabel(this);
    info->setText("总胜场：\n"
    "总场数：\n");
    info->setFixedSize(200, 200);
    info->setStyleSheet("font-family: 'Lobster'; font-size: 48px; color: black;");
    info->setAlignment(Qt::AlignTop);
    info->move(20, 10);
    info->show();
    level_info = new QLabel(this);
    level_info->setText("EXP：    /1000\n"
    "等级：\n");
    level_info->setFixedSize(400, 200);
    level_info->setStyleSheet("font-family: 'Lobster'; font-size: 48px; color: black;");
    level_info->setAlignment(Qt::AlignTop);
    level_info->move(500, 10);
    level_info->show();
    QString labelText = QString::number(Kingnum);
    kingnum = new QLabel(this);
    kingnum->setText(labelText);
    labelText = QString::number(Totalnum);
    totalnum = new QLabel(this);
    totalnum->setText(labelText);
    kingnum->setFixedSize(400, 400);
    kingnum->setStyleSheet("font-family: 'Lobster'; font-size: 48px; color: black;");
    kingnum->setAlignment(Qt::AlignTop);
    kingnum->move(200, 10);
    kingnum->show();
    totalnum->setFixedSize(400, 400);
    totalnum->setStyleSheet("font-family: 'Lobster'; font-size: 48px; color: black;");
    totalnum->setAlignment(Qt::AlignTop);
    totalnum->move(200, 67);
    totalnum->show();
    labelText = QString::number(Exp);
    exp = new QLabel(this);
    exp->setText(labelText);
    exp->setFixedSize(200, 200);
    exp->setStyleSheet("font-family: 'Lobster'; font-size: 48px; color: black;");
    exp->setAlignment(Qt::AlignTop);
    exp->move(620, 10);
    exp->show();
    labelText = QString::number(Level);
    level = new QLabel(this);
    level->setText(labelText);
    level->setFixedSize(200, 200);
    level->setStyleSheet("font-family: 'Lobster'; font-size: 48px; color: black;");
    level->setAlignment(Qt::AlignTop);
    level->move(660, 67);
    level->show();
    //刷新信息按钮
    Renew = new MyPushButton(this, 1, ":/res/Res/renew.png", ":/res/Res/renew.png");
    Renew->resize(30, 30);
    Renew->move(900, 0);
    Renew->setStyleSheet("font-size: 15px");
}

void BeginScene::paintEvent(QPaintEvent *event)
{//此函数只能命名为paintEvent，是QWidget的虚函数
    QWidget::paintEvent(event);
    QPainter painter(this);
    // 加载照片文件
    QImage image(":/res/Res/menu.png");
    // 在绘图设备上绘制照片
    painter.drawImage(rect(), image);
}

BeginScene::~BeginScene()
{
    delete bgm;
    delete start;
    delete setting;
    delete rule;
    delete Quitgame;
}

