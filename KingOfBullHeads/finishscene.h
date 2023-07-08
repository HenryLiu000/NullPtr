#ifndef FINISHSCENE_H
#define FINISHSCENE_H

#include<QObject>
#include <QWidget>
#include<QImage>
#include<QPainter>
#include<QSound>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QApplication>
#include <QLabel>
#include <QMovie>
#include"MyPushButton.h"

class FinishScene : public QWidget
{
public:
    FinishScene(QWidget* parent = 0);
    MyPushButton* Confirm;

};

#endif // FINISHSCENE_H
