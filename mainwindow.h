#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include <QtMultimedia/QSoundEffect>
#include <QSound>
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


private:
    Ui::MainWindow *ui;
public slots:
    void Start_Clicked();
    void Setting_Clicked();
    void Rule_Clicked();
    void Quitgame_Clicked();
    void QuitChooseMode_Clicked();
    void Guy2Choose();
    void Guy4Choose();
    void Guy2ChooseReturnToMainMenu();
    void Guy2ChooseReturnToChooseMode();
};
#endif // MAINWINDOW_H
