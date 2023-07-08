#ifndef AICHOOSECARD_H
#define AICHOOSECARD_H
#include <vector>
#include <QtGlobal>
#include <QRandomGenerator>
#include <QDateTime>
#include <random>
#include <algorithm>
#include <QList>
#include <card.h>
#include <QDebug>
namespace EasyAI
{
    int ChooseACard(std::vector<int> card)
    {
        qDebug()<<'1';
        std::mt19937 gen;
        gen.seed(123);
        std::sort(card.begin(),card.end());
        std::uniform_int_distribution<> dist(0, card.size() - 1);
        size_t randomIndex = dist(gen);
        int randomNumber = card[randomIndex];
        return randomNumber;
    }
    int ChooseARow(QList<MyCard*>& line1, QList<MyCard*>& line2, QList<MyCard*>& line3, QList<MyCard*>& line4)
    {
        int sum[4]{0,0,0,0};
        for(auto it:line1)
            sum[0] += it->heads_num;
        for(auto it:line2)
            sum[1] += it->heads_num;
        for(auto it:line3)
            sum[2] += it->heads_num;
        for(auto it:line4)
            sum[3] += it->heads_num;
        int min_index = -1;
        int min = 550;
        for(int i = 0;i < 4;i++)
        {
            if(sum[i] < min)
            {
                min = sum[i];
                min_index = i;
            }
        }
        return min_index;
    }
}
namespace NormAI
{
    int cal_heads_num(int number)
    {
        if(number%55==0) return 7;
        else if(number%11==0) return 5;
        else if(number%20==0) return 3;
        else if(number%5==0) return 2;
        else return 1;
    }
    int ChooseACard(std::vector<int> card,int opNumber,QList<MyCard*>& cards1,
                     QList<MyCard*>& cards2, QList<MyCard*>& cards3, QList<MyCard*>& cards4)
    {

        int myDscore = 100, opDscore = 0;
        int retNumber = 0;//初始化
        size_t len = card.size();
        for(size_t i = 0; i < len; i++)
        {
            int myNumber = card[i];
            size_t len1 = cards1.size(), len2 = cards2.size(), len3 = cards3.size(), len4 = cards4.size();
            std::vector<int> cards[4];
            std::vector<int> heads[4];
            for(size_t j = 0; j < len1; j++)
            {
                cards[0].push_back(cards1[j]->card_number);
                heads[0].push_back(cards1[j]->heads_num);
            }
            for(size_t j = 0; j < len2; j++)
            {
                cards[1].push_back(cards2[j]->card_number);
                heads[1].push_back(cards2[j]->heads_num);
            }
            for(size_t j = 0; j < len3; j++)
            {
                cards[2].push_back(cards3[j]->card_number);
                heads[2].push_back(cards3[j]->heads_num);
            }
            for(size_t j = 0; j < len4; j++)
            {
                cards[3].push_back(cards4[j]->card_number);
                heads[3].push_back(cards4[j]->heads_num);
            }
            size_t l[4];
            for(size_t j = 0; j < 4; j++)
            {
                l[j] = cards[j].size();
            }
//            qDebug() << "myNum = " << myNumber ;
            if(myNumber < opNumber)
            {  //AI先放牌
//                qDebug() << "AI先" ;
                if(len1 < 5 && len2 < 5 && len3 < 5 && len4 < 5)
                {  //如果每一行都小于5张
//                    qDebug() << " 每一行都小于5张" ;
                    int delta[4] = {105, 105, 105, 105};
                    int min_idx = -1, min = 105;
                    for(int j=0; j < 4; j++)
                    {
                        if(myNumber > *cards[j].rbegin())
                        {
                            delta[j] = myNumber - (*cards[j].rbegin());
                        }
                        if(delta[j] < min)
                        {
                            min = delta[j];
                            min_idx = j;
                        }
                    }
                    //如果myNumber比所有的末尾牌都小，那么选择一列收走
                    if(min_idx == -1)
                    {
//                        qDebug() << "  myNumber比所有的末尾牌都小" ;
                        int min_i = 0, min_heads = 100;
                        for(int j=0; j<4; j++)
                        {
                            int tmp = 0;
                            for(size_t k=0; k < cards[j].size(); k++)
                            {
                                tmp += heads[j][k];
                            }
                            if(tmp < min_heads)
                            {
                                min_heads = tmp;
                                min_i = j;
                            }
                        }
                        if(min_heads < myDscore - opDscore)
                        {
                            myDscore = min_heads;
                            opDscore = 0;
                            retNumber = myNumber;
                        }
                    }
                    else
                    {
//                        qDebug() << "  不是这样的" ;
//                        qDebug() << "   目前：myDScore = " << myDscore << " opDScore = " << opDscore ;
                        cards[min_idx].push_back(myNumber);
                        heads[min_idx].push_back(cal_heads_num(myNumber));
                        int delta0[4] = {105, 105, 105, 105};
                        int min_idx0 = -1, min0 = 105;
                        for(int j=0; j<4; j++)
                        {
                            if(opNumber > *cards[j].rbegin())
                            {
                                delta0[j] = opNumber - *cards[j].rbegin();
                            }
                            if(delta0[j] < min0)
                            {
                                min0 = delta0[j];
                                min_idx0 = j;
                            }
                        }
                        if(min_idx0 == -1)
                        {
                            int min_i = 0, min_heads = 100;
                            for(int j=0; j<4; j++){
                                int tmp = 0;
                                for(size_t k=0; k < cards[j].size(); k++)
                                {
                                    tmp += heads[j][k];
                                }
                                if(tmp < min_heads){
                                    min_heads = tmp;
                                    min_i = j;
                                }
                            }
                            if(-min_heads < myDscore - opDscore){
                                myDscore = 0;
                                opDscore = min_heads;
                                retNumber = myNumber;
                            }
                        }
                        else
                        {
                            if(cards[min_idx].size() == 5)
                            {
                                int min_heads = 0;
                                for(int j=0; j<5; j++)
                                {
                                    min_heads += heads[min_idx][j];
                                }
                                if(-min_heads < myDscore - opDscore)
                                {
                                    myDscore = 0;
                                    opDscore = min_heads;
                                    retNumber = myNumber;
                                }
                            }
                            else{
                                if(0 < myDscore - opDscore){
                                    myDscore = 0;
                                    opDscore = 0;
                                    retNumber = myNumber;
                                }
                            }
                        }
                    }
                }
                else
                {
//                    qDebug() << "有一排5张了" ;
                    int delta[4] = {105, 105, 105, 105};
                    int min_idx = -1, min = 105;
                    for(int j=0; j<4; j++)
                    {
                        if(myNumber > *cards[j].rbegin())
                        {
                            delta[j] = myNumber - (*cards[j].rbegin());
                        }
                        if(delta[j] < min)
                        {
                            min = delta[j];
                            min_idx = j;
                        }
                    }
                    //如果myNumber比所有的末尾牌都小，那么选择一列收走
                    if(min_idx == -1)
                    {
                        int min_i = 0, min_heads = 100;
                        for(int j=0; j<4; j++)
                        {
                            int tmp = 0;
                            for(size_t k = 0; k < cards[j].size(); k++)
                            {
                                tmp += heads[j][k];
                            }
                            if(tmp < min_heads)
                            {
                                min_heads = tmp;
                                min_i = j;
                            }
                        }
                        cards[min_i].clear();
                        heads[min_i].clear();
                        cards[min_i].push_back(myNumber);
                        heads[min_i].push_back(cal_heads_num(myNumber));
                        l[min_i] = 1;
                        int delta0[4] = {105, 105, 105, 105};
                        int min_idx0 = -1, min0 = 105;
                        for(int j=0; j<4; j++)
                        {
                            if(opNumber > *cards[j].rbegin())
                            {
                                delta0[j] = opNumber - *cards[j].rbegin();
                            }
                            if(delta0[j] < min0)
                            {
                                min0 = delta0[j];
                                min_idx0 = j;
                            }
                        }
                        int heads_num0 = 0;
                        if(cards[min_idx0].size() == 5)
                        {
                            for(int k=0; k<5; k++)
                            {
                                heads_num0 += heads[min_idx0][k];
                            }
                        }
                        if(min_heads - heads_num0 < myDscore - opDscore)
                        {
                            myDscore = min_heads;
                            opDscore = heads_num0;
                            retNumber = myNumber;
                        }
                    }
                    else{
                        int bull_heads = 0, bull_heads0 = 0;
                        if(l[min_idx] == 5)
                        {
                            for(int j=0; j<5; j++)
                            {
                                bull_heads += heads[min_idx][j];
                            }
                            cards[min_idx].clear();
                            heads[min_idx].clear();
                            cards[min_idx].push_back(myNumber);
                            heads[min_idx].push_back(cal_heads_num(myNumber));
                            l[min_idx] = 1;
                        }
                        else{
                            cards[min_idx].push_back(myNumber);
                            heads[min_idx].push_back(cal_heads_num(myNumber));
                            l[min_idx] ++;
                        }
                        int delta0[4] = {105, 105, 105, 105};
                        int min_idx0 = -1, min0 = 105;
                        for(int j=0; j<4; j++)
                        {
                            if(opNumber > *cards[j].rbegin())
                            {
                                delta0[j] = opNumber - *cards[j].rbegin();
                            }
                            if(delta0[j] < min0){
                                min0 = delta0[j];
                                min_idx0 = j;
                            }
                        }
                        if(l[min_idx0] == 5)
                        {
                            for(int j=0; j<5; j++)
                            {
                                bull_heads0 += heads[min_idx0][j];
                            }
                        }
                        if(bull_heads - bull_heads0 < myDscore - opDscore)
                        {
                            myDscore = bull_heads;
                            opDscore = bull_heads0;
                            retNumber = myNumber;
                        }
                    }
                }
            }
            //玩家先放牌
            else
            {
//                qDebug() << "PC先" ;
                if(len1 < 5 && len2 < 5 && len3 < 5 && len4 < 5)
                {  //如果每一行都小于5张
                    int delta[4] = {105, 105, 105, 105};
                    int min_idx = -1, min = 105;
                    for(int j=0; j<4; j++)
                    {
                        if(opNumber > *cards[j].rbegin()){
                            delta[j] = opNumber - (*cards[j].rbegin());
                        }
                        if(delta[j] < min){
                            min = delta[j];
                            min_idx = j;
                        }
                    }
                    //如果myNumber比所有的末尾牌都小，那么选择一列收走
                    if(min_idx == -1)
                    {
                        int min_i = 0, min_heads = 100;
                        for(int j=0; j<4; j++)
                        {
                            int tmp = 0;
                            for(int k=0; k<cards[j].size(); k++){
                                tmp += heads[j][k];
                            }
                            if(tmp < min_heads){
                                min_heads = tmp;
                                min_i = j;
                            }
                        }
                        if(- min_heads < myDscore - opDscore)
                        {
                            myDscore = 0;
                            opDscore = min_heads;
                            retNumber = myNumber;
                        }
                    }
                    else
                    {
                        cards[min_idx].push_back(opNumber);
                        heads[min_idx].push_back(cal_heads_num(opNumber));
                        int delta0[4] = {105, 105, 105, 105};
                        int min_idx0 = -1, min0 = 105;
                        for(int j=0; j<4; j++){
                            if(myNumber > *cards[j].rbegin()){
                                delta0[j] = myNumber - *cards[j].rbegin();
                            }
                            if(delta0[j] < min0){
                                min0 = delta0[j];
                                min_idx0 = j;
                            }
                        }
                        if(min_idx0 == -1)
                        {
                            int min_i = 0, min_heads = 100;
                            for(int j=0; j<4; j++)
                            {
                                int tmp = 0;
                                for(size_t k = 0; k < cards[j].size(); k++)
                                {
                                    tmp += heads[j][k];
                                }
                                if(tmp < min_heads)
                                {
                                    min_heads = tmp;
                                    min_i = j;
                                }
                            }
                            if(min_heads < myDscore - opDscore)
                            {
                                myDscore = min_heads;
                                opDscore = 0;
                                retNumber = myNumber;
                            }
                        }
                        else
                        {
                            if(cards[min_idx].size() == 5)
                            {
                                int min_heads = 0;
                                for(int j=0; j<5; j++)
                                {
                                    min_heads += heads[min_idx][j];
                                }
                                if(min_heads < myDscore - opDscore)
                                {
                                    myDscore = 0;
                                    opDscore = min_heads;
                                    retNumber = myNumber;
                                }
                            }
                            else{
                                if(0 < myDscore - opDscore){
                                    myDscore = 0;
                                    opDscore = 0;
                                    retNumber = myNumber;
                                }
                            }
                        }
                    }
                }
                else
                {
                    int delta[4] = {105, 105, 105, 105};
                    int min_idx = -1, min = 105;
                    for(int j=0; j<4; j++)
                    {
                        if(opNumber > *cards[j].rbegin())
                        {
                            delta[j] = opNumber - (*cards[j].rbegin());
                        }
                        if(delta[j] < min)
                        {
                            min = delta[j];
                            min_idx = j;
                        }
                    }
                    //如果opNumber比所有的末尾牌都小，那么选择一列收走
                    if(min_idx == -1)
                    {
                        int min_i = 0, min_heads = 100;
                        for(int j=0; j<4; j++)
                        {
                            int tmp = 0;
                            for(size_t k=0; k<cards[j].size(); k++){
                                tmp += heads[j][k];
                            }
                            if(tmp < min_heads){
                                min_heads = tmp;
                                min_i = j;
                            }
                        }
                        cards[min_i].clear();
                        heads[min_i].clear();
                        cards[min_i].push_back(opNumber);
                        heads[min_i].push_back(cal_heads_num(opNumber));
                        l[min_i] = 1;
                        int delta0[4] = {105, 105, 105, 105};
                        int min_idx0 = -1, min0 = 105;
                        for(int j=0; j<4; j++){
                            if(myNumber > *cards[j].rbegin()){
                                delta0[j] = myNumber - *cards[j].rbegin();
                            }
                            if(delta0[j] < min0){
                                min0 = delta0[j];
                                min_idx0 = j;
                            }
                        }
                        int heads_num0 = 0;
                        if(cards[min_idx0].size() == 5)
                        {
                            for(int k=0; k<5; k++){
                                heads_num0 += heads[min_idx0][k];
                            }
                        }
                        if(heads_num0 - min_heads < myDscore - opDscore)
                        {
                            myDscore = heads_num0;
                            opDscore = min_heads;
                            retNumber = myNumber;
                        }
                    }
                    else
                    {
                        int bull_heads = 0, bull_heads0 = 0;
                        if(l[min_idx] == 5)
                        {
                            for(int j=0; j<5; j++)
                            {
                                bull_heads += heads[min_idx][j];
                            }
                            cards[min_idx].clear();
                            heads[min_idx].clear();
                            cards[min_idx].push_back(opNumber);
                            heads[min_idx].push_back(cal_heads_num(opNumber));
                            l[min_idx] = 1;
                        }
                        else
                        {
                            cards[min_idx].push_back(opNumber);
                            heads[min_idx].push_back(cal_heads_num(opNumber));
                            l[min_idx] ++;
                        }
                        int delta0[4] = {105, 105, 105, 105};
                        int min_idx0 = -1, min0 = 105;
                        for(int j=0; j<4; j++)
                        {
                            if(myNumber > *cards[j].rbegin())
                            {
                                delta0[j] = myNumber - *cards[j].rbegin();
                            }
                            if(delta0[j] < min0)
                            {
                                min0 = delta0[j];
                                min_idx0 = j;
                            }
                        }
                        if(l[min_idx0] == 5)
                        {
                            for(int j=0; j<5; j++)
                            {
                                bull_heads0 += heads[min_idx0][j];
                            }
                        }
                        if(bull_heads0 - bull_heads < myDscore - opDscore)
                        {
                            myDscore = bull_heads0;
                            opDscore = bull_heads;
                            retNumber = myNumber;
                        }
                    }
                }
            }
        }
        return retNumber;

    }

}
namespace HardAI
{
int cal_heads_num(int number)
{
    if(number%55==0) return 7;
    else if(number%11==0) return 5;
    else if(number%20==0) return 3;
    else if(number%5==0) return 2;
    else return 1;
}
int ChooseACard(std::vector<int>& card,int opNumber,QList<MyCard*>& cards1,
                 QList<MyCard*>& cards2, QList<MyCard*>& cards3, QList<MyCard*>& cards4,
                std::vector<int>& card_pool)
{

    int myDscore = 100, opDscore = 0;
    int retNumber = 0;//初始化
    quint32 seed = static_cast<quint32>(QDateTime::currentMSecsSinceEpoch());
    QRandomGenerator random(seed);
    int lowerBound = 1;
    int upperBound = 104;

    std::vector<int> numbers;
    for (int i = lowerBound; i <= upperBound; ++i)
    {
        numbers.push_back(i);
    }
    for (int i = numbers.size() - 1; i > 0; --i) {
        int j = random.bounded(i + 1);
        int tmp = numbers[i];
        numbers[i] = numbers[j];
        numbers[j] = tmp;
    }
    for(int i = 1; i <= 104; i++)
    {
        bool can_has = 1;
        for(size_t j=0; j<card_pool.size(); j++){
            if(numbers[i] == card_pool[j]){
                can_has = 0;
                break;
            }
        }
        if(!can_has) continue;
        int myNumber = numbers[i];
        size_t len1 = cards1.size(), len2 = cards2.size(), len3 = cards3.size(), len4 = cards4.size();
        std::vector<int> cards[4];
        std::vector<int> heads[4];
        for(size_t j = 0; j < len1; j++)
        {
            cards[0].push_back(cards1[j]->card_number);
            heads[0].push_back(cards1[j]->heads_num);
        }
        for(size_t j = 0; j < len2; j++)
        {
            cards[1].push_back(cards2[j]->card_number);
            heads[1].push_back(cards2[j]->heads_num);
        }
        for(size_t j = 0; j < len3; j++)
        {
            cards[2].push_back(cards3[j]->card_number);
            heads[2].push_back(cards3[j]->heads_num);
        }
        for(size_t j = 0; j < len4; j++)
        {
            cards[3].push_back(cards4[j]->card_number);
            heads[3].push_back(cards4[j]->heads_num);
        }
        size_t l[4];
        for(size_t j = 0; j < 4; j++)
        {
            l[j] = cards[j].size();
        }
        if(myNumber < opNumber)
        {  //AI先放牌
            if(len1 < 5 && len2 < 5 && len3 < 5 && len4 < 5)
            {  //如果每一行都小于5张
                int delta[4] = {105, 105, 105, 105};
                int min_idx = -1, min = 105;
                for(int j=0; j < 4; j++)
                {
                    if(myNumber > *cards[j].rbegin())
                    {
                        delta[j] = myNumber - (*cards[j].rbegin());
                    }
                    if(delta[j] < min)
                    {
                        min = delta[j];
                        min_idx = j;
                    }
                }
                //如果myNumber比所有的末尾牌都小，那么选择一列收走
                if(min_idx == -1)
                {
                    int min_i = 0, min_heads = 100;
                    for(int j=0; j<4; j++)
                    {
                        int tmp = 0;
                        for(size_t k=0; k < cards[j].size(); k++)
                        {
                            tmp += heads[j][k];
                        }
                        if(tmp < min_heads)
                        {
                            min_heads = tmp;
                            min_i = j;
                        }
                    }
                    if(min_heads < myDscore - opDscore)
                    {
                        myDscore = min_heads;
                        opDscore = 0;
                        retNumber = myNumber;
                    }
                }
                else
                {
//                        qDebug() << "  不是这样的" ;
//                        qDebug() << "   目前：myDScore = " << myDscore << " opDScore = " << opDscore ;
                    cards[min_idx].push_back(myNumber);
                    heads[min_idx].push_back(cal_heads_num(myNumber));
                    int delta0[4] = {105, 105, 105, 105};
                    int min_idx0 = -1, min0 = 105;
                    for(int j=0; j<4; j++)
                    {
                        if(opNumber > *cards[j].rbegin())
                        {
                            delta0[j] = opNumber - *cards[j].rbegin();
                        }
                        if(delta0[j] < min0)
                        {
                            min0 = delta0[j];
                            min_idx0 = j;
                        }
                    }
                    if(min_idx0 == -1)
                    {
                        int min_i = 0, min_heads = 100;
                        for(int j=0; j<4; j++){
                            int tmp = 0;
                            for(size_t k=0; k < cards[j].size(); k++)
                            {
                                tmp += heads[j][k];
                            }
                            if(tmp < min_heads){
                                min_heads = tmp;
                                min_i = j;
                            }
                        }
                        if(-min_heads < myDscore - opDscore){
                            myDscore = 0;
                            opDscore = min_heads;
                            retNumber = myNumber;
                        }
                    }
                    else
                    {
                        if(cards[min_idx].size() == 5)
                        {
                            int min_heads = 0;
                            for(int j=0; j<5; j++)
                            {
                                min_heads += heads[min_idx][j];
                            }
                            if(-min_heads < myDscore - opDscore)
                            {
                                myDscore = 0;
                                opDscore = min_heads;
                                retNumber = myNumber;
                            }
                        }
                        else{
                            if(0 < myDscore - opDscore){
                                myDscore = 0;
                                opDscore = 0;
                                retNumber = myNumber;
                            }
                        }
                    }
                }
            }
            else
            {
//                    qDebug() << "有一排5张了" ;
                int delta[4] = {105, 105, 105, 105};
                int min_idx = -1, min = 105;
                for(int j=0; j<4; j++)
                {
                    if(myNumber > *cards[j].rbegin())
                    {
                        delta[j] = myNumber - (*cards[j].rbegin());
                    }
                    if(delta[j] < min)
                    {
                        min = delta[j];
                        min_idx = j;
                    }
                }
                //如果myNumber比所有的末尾牌都小，那么选择一列收走
                if(min_idx == -1)
                {
                    int min_i = 0, min_heads = 100;
                    for(int j=0; j<4; j++)
                    {
                        int tmp = 0;
                        for(size_t k = 0; k < cards[j].size(); k++)
                        {
                            tmp += heads[j][k];
                        }
                        if(tmp < min_heads)
                        {
                            min_heads = tmp;
                            min_i = j;
                        }
                    }
                    cards[min_i].clear();
                    heads[min_i].clear();
                    cards[min_i].push_back(myNumber);
                    heads[min_i].push_back(cal_heads_num(myNumber));
                    l[min_i] = 1;
                    int delta0[4] = {105, 105, 105, 105};
                    int min_idx0 = -1, min0 = 105;
                    for(int j=0; j<4; j++)
                    {
                        if(opNumber > *cards[j].rbegin())
                        {
                            delta0[j] = opNumber - *cards[j].rbegin();
                        }
                        if(delta0[j] < min0)
                        {
                            min0 = delta0[j];
                            min_idx0 = j;
                        }
                    }
                    int heads_num0 = 0;
                    if(cards[min_idx0].size() == 5)
                    {
                        for(int k=0; k<5; k++)
                        {
                            heads_num0 += heads[min_idx0][k];
                        }
                    }
                    if(min_heads - heads_num0 < myDscore - opDscore)
                    {
                        myDscore = min_heads;
                        opDscore = heads_num0;
                        retNumber = myNumber;
                    }
                }
                else{
                    int bull_heads = 0, bull_heads0 = 0;
                    if(l[min_idx] == 5)
                    {
                        for(int j=0; j<5; j++)
                        {
                            bull_heads += heads[min_idx][j];
                        }
                        cards[min_idx].clear();
                        heads[min_idx].clear();
                        cards[min_idx].push_back(myNumber);
                        heads[min_idx].push_back(cal_heads_num(myNumber));
                        l[min_idx] = 1;
                    }
                    else{
                        cards[min_idx].push_back(myNumber);
                        heads[min_idx].push_back(cal_heads_num(myNumber));
                        l[min_idx] ++;
                    }
                    int delta0[4] = {105, 105, 105, 105};
                    int min_idx0 = -1, min0 = 105;
                    for(int j=0; j<4; j++)
                    {
                        if(opNumber > *cards[j].rbegin())
                        {
                            delta0[j] = opNumber - *cards[j].rbegin();
                        }
                        if(delta0[j] < min0){
                            min0 = delta0[j];
                            min_idx0 = j;
                        }
                    }
                    if(l[min_idx0] == 5)
                    {
                        for(int j=0; j<5; j++)
                        {
                            bull_heads0 += heads[min_idx0][j];
                        }
                    }
                    if(bull_heads - bull_heads0 < myDscore - opDscore)
                    {
                        myDscore = bull_heads;
                        opDscore = bull_heads0;
                        retNumber = myNumber;
                    }
                }
            }
        }
        //玩家先放牌
        else
        {
//                qDebug() << "PC先" ;
            if(len1 < 5 && len2 < 5 && len3 < 5 && len4 < 5)
            {  //如果每一行都小于5张
                int delta[4] = {105, 105, 105, 105};
                int min_idx = -1, min = 105;
                for(int j=0; j<4; j++)
                {
                    if(opNumber > *cards[j].rbegin()){
                        delta[j] = opNumber - (*cards[j].rbegin());
                    }
                    if(delta[j] < min){
                        min = delta[j];
                        min_idx = j;
                    }
                }
                //如果myNumber比所有的末尾牌都小，那么选择一列收走
                if(min_idx == -1)
                {
                    int min_i = 0, min_heads = 100;
                    for(int j=0; j<4; j++)
                    {
                        int tmp = 0;
                        for(int k=0; k<cards[j].size(); k++){
                            tmp += heads[j][k];
                        }
                        if(tmp < min_heads){
                            min_heads = tmp;
                            min_i = j;
                        }
                    }
                    if(- min_heads < myDscore - opDscore)
                    {
                        myDscore = 0;
                        opDscore = min_heads;
                        retNumber = myNumber;
                    }
                }
                else
                {
                    cards[min_idx].push_back(opNumber);
                    heads[min_idx].push_back(cal_heads_num(opNumber));
                    int delta0[4] = {105, 105, 105, 105};
                    int min_idx0 = -1, min0 = 105;
                    for(int j=0; j<4; j++){
                        if(myNumber > *cards[j].rbegin()){
                            delta0[j] = myNumber - *cards[j].rbegin();
                        }
                        if(delta0[j] < min0){
                            min0 = delta0[j];
                            min_idx0 = j;
                        }
                    }
                    if(min_idx0 == -1)
                    {
                        int min_i = 0, min_heads = 100;
                        for(int j=0; j<4; j++)
                        {
                            int tmp = 0;
                            for(size_t k = 0; k < cards[j].size(); k++)
                            {
                                tmp += heads[j][k];
                            }
                            if(tmp < min_heads)
                            {
                                min_heads = tmp;
                                min_i = j;
                            }
                        }
                        if(min_heads < myDscore - opDscore)
                        {
                            myDscore = min_heads;
                            opDscore = 0;
                            retNumber = myNumber;
                        }
                    }
                    else
                    {
                        if(cards[min_idx].size() == 5)
                        {
                            int min_heads = 0;
                            for(int j=0; j<5; j++)
                            {
                                min_heads += heads[min_idx][j];
                            }
                            if(min_heads < myDscore - opDscore)
                            {
                                myDscore = 0;
                                opDscore = min_heads;
                                retNumber = myNumber;
                            }
                        }
                        else{
                            if(0 < myDscore - opDscore){
                                myDscore = 0;
                                opDscore = 0;
                                retNumber = myNumber;
                            }
                        }
                    }
                }
            }
            else
            {
                int delta[4] = {105, 105, 105, 105};
                int min_idx = -1, min = 105;
                for(int j=0; j<4; j++)
                {
                    if(opNumber > *cards[j].rbegin())
                    {
                        delta[j] = opNumber - (*cards[j].rbegin());
                    }
                    if(delta[j] < min)
                    {
                        min = delta[j];
                        min_idx = j;
                    }
                }
                //如果opNumber比所有的末尾牌都小，那么选择一列收走
                if(min_idx == -1)
                {
                    int min_i = 0, min_heads = 100;
                    for(int j=0; j<4; j++)
                    {
                        int tmp = 0;
                        for(size_t k=0; k<cards[j].size(); k++){
                            tmp += heads[j][k];
                        }
                        if(tmp < min_heads){
                            min_heads = tmp;
                            min_i = j;
                        }
                    }
                    cards[min_i].clear();
                    heads[min_i].clear();
                    cards[min_i].push_back(opNumber);
                    heads[min_i].push_back(cal_heads_num(opNumber));
                    l[min_i] = 1;
                    int delta0[4] = {105, 105, 105, 105};
                    int min_idx0 = -1, min0 = 105;
                    for(int j=0; j<4; j++){
                        if(myNumber > *cards[j].rbegin()){
                            delta0[j] = myNumber - *cards[j].rbegin();
                        }
                        if(delta0[j] < min0){
                            min0 = delta0[j];
                            min_idx0 = j;
                        }
                    }
                    int heads_num0 = 0;
                    if(cards[min_idx0].size() == 5)
                    {
                        for(int k=0; k<5; k++){
                            heads_num0 += heads[min_idx0][k];
                        }
                    }
                    if(heads_num0 - min_heads < myDscore - opDscore)
                    {
                        myDscore = heads_num0;
                        opDscore = min_heads;
                        retNumber = myNumber;
                    }
                }
                else
                {
                    int bull_heads = 0, bull_heads0 = 0;
                    if(l[min_idx] == 5)
                    {
                        for(int j=0; j<5; j++)
                        {
                            bull_heads += heads[min_idx][j];
                        }
                        cards[min_idx].clear();
                        heads[min_idx].clear();
                        cards[min_idx].push_back(opNumber);
                        heads[min_idx].push_back(cal_heads_num(opNumber));
                        l[min_idx] = 1;
                    }
                    else
                    {
                        cards[min_idx].push_back(opNumber);
                        heads[min_idx].push_back(cal_heads_num(opNumber));
                        l[min_idx] ++;
                    }
                    int delta0[4] = {105, 105, 105, 105};
                    int min_idx0 = -1, min0 = 105;
                    for(int j=0; j<4; j++)
                    {
                        if(myNumber > *cards[j].rbegin())
                        {
                            delta0[j] = myNumber - *cards[j].rbegin();
                        }
                        if(delta0[j] < min0)
                        {
                            min0 = delta0[j];
                            min_idx0 = j;
                        }
                    }
                    if(l[min_idx0] == 5)
                    {
                        for(int j=0; j<5; j++)
                        {
                            bull_heads0 += heads[min_idx0][j];
                        }
                    }
                    if(bull_heads0 - bull_heads < myDscore - opDscore)
                    {
                        myDscore = bull_heads0;
                        opDscore = bull_heads;
                        retNumber = myNumber;
                    }
                }
            }
        }
    }
    bool is_in = 0;
    for(size_t i=0; i<card.size(); i++){
        if(card[i] == retNumber){
            is_in = 1;
            break;
        }
    }
    if(!is_in){
        card.pop_back();
        card.push_back(retNumber);
    }
    card_pool.push_back(retNumber);
    return retNumber;

}

}
#endif // AICHOOSECARD_H
