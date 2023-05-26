#ifndef CHOOSEMODE_H
#define CHOOSEMODE_H

#endif // CHOOSEMODE_H
#include<QObject>
#include <QWidget>
#include<QImage>
#include<QPainter>
#include<QSound>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include"MyPushButton.h"
class ChooseModeScene:public QWidget
{
    Q_OBJECT
public:
    explicit ChooseModeScene(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);
    QSound* bgm;
    QPushButton *Guy2;
    QPushButton *Guy4;
    QPushButton *Quit;
signals:

public slots:


};
