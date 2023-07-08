#ifndef SETTINGS_H
#define SETTINGS_H

#endif // SETTINGS_H
#include<QObject>
#include <QWidget>
#include<QImage>
#include<QPainter>
#include<QSound>
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include"MyPushButton.h"
class SettingScene:public QWidget
{
    Q_OBJECT
public:
    explicit SettingScene(QWidget *parent = 0);
    ~SettingScene();
    void paintEvent(QPaintEvent *event);
    QSlider* setVolume;
    QPushButton *Quit;
signals:

public slots:


};
