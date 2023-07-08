#ifndef GUY4PLAYMODECHOOSE_H
#define GUY4PLAYMODECHOOSE_H

#endif // GUY4PLAYMODECHOOSE_H

#include<QObject>
#include <QWidget>
#include<QImage>
#include<QPainter>
#include<QSound>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include"MyPushButton.h"
class Guy4PlayModeChoose:public QWidget
{
    Q_OBJECT
public:
    explicit Guy4PlayModeChoose(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);
    QSound* bgm;
    QPushButton *Easy;
    QPushButton *Medium;
    QPushButton *Hard;
    QPushButton *Return;
    QPushButton *MainMenu;
signals:

public slots:
};
