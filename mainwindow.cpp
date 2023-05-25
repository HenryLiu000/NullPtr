#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "MyPushButton.h"
#include "beginscene.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/res/Res/Icon.ico"));
    setWindowTitle("Who is the king of bull heads?");
    QSound* bgm;
    bgm=new QSound("qrc:/res/Res/battlebgm.wav");
    bgm->setLoops(-1);
    bgm->play();
//    ui->stackedWidget->setCurrentIndex(0);
    MyPushButton* begin2game = new MyPushButton(this,true,":/res/Res/Icon.ico",":/res/Res/Icon.ico");
    begin2game->move(100, 100);
    connect(begin2game, &MyPushButton::clicked, [=](){
        bgm->stop();
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

