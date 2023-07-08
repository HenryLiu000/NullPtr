#ifndef PLAYER_H
#define PLAYER_H

#include <QLabel>
#include <QMovie>
#include <QSound>
#include <QTimer>
#include <QGraphicsColorizeEffect>
#include <QList>
#include "card.h"

class MyPlayer:public QLabel
{
public:
    int cards_num;
    int heads_num;
    std::vector<int> cards_in_hands;
    QString player_name;
    QString avatar_PATH;
    MyPlayer(QWidget *parent, QString _name, QString _PATH);
    void play_a_card();
};

#endif // PLAYER_H
