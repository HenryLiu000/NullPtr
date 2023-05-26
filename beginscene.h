#ifndef BEGINSCENE_H
#define BEGINSCENE_H

#include<QObject>
#include <QWidget>
#include<QImage>
#include<QPainter>
#include<QSound>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include"MyPushButton.h"

class BeginScene : public QWidget
{
    Q_OBJECT
public:
    explicit BeginScene(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);
    QSound* bgm;
    QPushButton *start;
    QPushButton *setting;
    QPushButton *rule;
    QPushButton *Quitgame;
signals:

public slots:

};

#endif // BEGINSCENE_H
