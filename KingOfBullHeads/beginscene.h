#ifndef BEGINSCENE_H
#define BEGINSCENE_H

#include <QObject>
#include <QLabel>
#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QSound>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFile>
#include <QDataStream>
#include "MyPushButton.h"

class BeginScene : public QWidget
{
    Q_OBJECT
public:
    explicit BeginScene(QWidget *parent = 0);
    ~BeginScene();
    void paintEvent(QPaintEvent *event);
    QSound* bgm;
    QPushButton *start;
    QPushButton *setting;
    QPushButton *rule;
    QPushButton *Quitgame;
    MyPushButton *Renew;
    QLabel *info;
    QLabel *level_info;
    QLabel *kingnum;
    QLabel *totalnum;
    QLabel *exp;
    QLabel *level;
    QFile *file;
    int Kingnum;
    int Totalnum;
    int Exp;
    int Level;
signals:
public slots:
};

#endif // BEGINSCENE_H
