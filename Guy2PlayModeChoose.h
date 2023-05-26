#ifndef GUY2PLAYMODECHOOSE_H
#define GUY2PLAYMODECHOOSE_H

#endif // GUY2PLAYMODECHOOSE_H
#include<QObject>
#include <QWidget>
#include<QImage>
#include<QPainter>
#include<QSound>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include"MyPushButton.h"
class Guy2PlayModeChoose:public QWidget
{
    Q_OBJECT
public:
    explicit Guy2PlayModeChoose(QWidget *parent = 0);
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
