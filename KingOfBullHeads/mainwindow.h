#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include <QtMultimedia/QSoundEffect>
#include <QSound>
#include <QTimer>
#include <QEventLoop>
#include "MyPushButton.h"
//QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
//QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    //void paintEvent(QPaintEvent *event);
    ~MainWindow();
    std::vector<int> card_pool;


private:
    Ui::MainWindow *ui;

public slots:
    void Start_Clicked();
    void Setting_Clicked();
    void Rule_Clicked();
    void Quitgame_Clicked();
    void QuitChooseMode_Clicked();
    void RenewInfo();

    void Guy2Choose();
    void Guy4Choose();

    void Guy2ChooseReturnToMainMenu();
    void Guy2ChooseReturnToChooseMode();

    void Guy4ChooseReturnToMainMenu();
    void Guy4ChooseReturnToChooseMode();

    void EasyPlay1v1();
    void NormalPlay1v1();
    void HardPlay1v1();

    void EasyPlay1v3();
    void NormalPlay1v3();
    void HardPlay1v3();

    void Play1v1ConfirmCreatePlayer();
    void SomeCard_Clicked();
    void Cancel_Play_Card();
    void Confirm_Play_Card();

    void SomeCard_Clicked_3();
    void Cancel_Play_Card_3();
    void Confirm_Play_Card_3();
    void Play1v3ConfirmCreatePlayer();
    void Play1v1ToBeginscene();
    void Play1v3ToBeginscene();

    void finish_a_game();
    void finish_1v3_game();
};
#endif // MAINWINDOW_H
