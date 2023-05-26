#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "MyPushButton.h"
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <beginscene.h>
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
}
void MainWindow::Start_Clicked()
{
    ui->choosemodescene = new ChooseModeScene();
    ui->stackedWidget->addWidget(ui->choosemodescene);
    ui->stackedWidget->setCurrentIndex(1);
    connect(ui->choosemodescene->Quit,&MyPushButton::clicked,this,&MainWindow::QuitChooseMode_Clicked);
    connect(ui->choosemodescene->Guy2,&MyPushButton::clicked,this,&MainWindow::Guy2Choose);
    connect(ui->choosemodescene->Guy4,&MyPushButton::clicked,this,&MainWindow::Guy4Choose);
}

//MainMenu按钮
void MainWindow::Setting_Clicked()
{

}
void MainWindow::Rule_Clicked()
{

}
void MainWindow::Quitgame_Clicked()
{
    delete ui->stackedWidget->widget(0);
    this->close();
}
void MainWindow::QuitChooseMode_Clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    //ui->beginscene->bgm->play();刷夜勿用
    delete ui->stackedWidget->widget(1);
}

//人数选择按钮
void MainWindow::Guy2Choose()
{
    ui->Guy2modescene = new Guy2PlayModeChoose();
    ui->stackedWidget->addWidget(ui->Guy2modescene);
    ui->stackedWidget->setCurrentIndex(2);
    connect(ui->Guy2modescene->MainMenu,&MyPushButton::clicked,this,&MainWindow::Guy2ChooseReturnToMainMenu);
    connect(ui->Guy2modescene->Return,&MyPushButton::clicked,this,&MainWindow::Guy2ChooseReturnToChooseMode);
}
void MainWindow::Guy4Choose()
{

}

//二人对战操作
void MainWindow::Guy2ChooseReturnToMainMenu()
{
    ui->stackedWidget->setCurrentIndex(0);
    //ui->beginscene->bgm->play();刷夜勿用
    delete ui->stackedWidget->widget(2);
    delete ui->stackedWidget->widget(1);
}
void MainWindow::Guy2ChooseReturnToChooseMode()
{
    ui->stackedWidget->setCurrentIndex(1);
    //ui->beginscene->bgm->play();刷夜勿用
    delete ui->stackedWidget->widget(2);
}
MainWindow::~MainWindow()
{
    delete ui;
}

