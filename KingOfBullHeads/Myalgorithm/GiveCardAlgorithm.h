#ifndef GIVECARDALGORITHM_H
#define GIVECARDALGORITHM_H
#include <QtGlobal>
#include <QRandomGenerator>
#include <QDateTime>
#include <vector>
#include <random>
#include <algorithm>
namespace GiveCard
{
    class ThreeUnion
    {
    public:
        std::vector<int> v1;
        std::vector<int> v2;
        std::vector<int> v3;
        ThreeUnion(const std::vector<int>& a1,const std::vector<int>& a2,const std::vector<int>& a3):v1(a1),v2(a2),v3(a3){};
    };
    class FiveUnion
    {
    public:
        std::vector<int> v1;
        std::vector<int> v2;
        std::vector<int> v3;
        std::vector<int> v4;
        std::vector<int> v5;
        FiveUnion(const std::vector<int>& a1,const std::vector<int>& a2,const std::vector<int>& a3,const std::vector<int>& a4,const std::vector<int>& a5):v1(a1),v2(a2),v3(a3),v4(a4),v5(a5){};
    };

    ThreeUnion Init1v1()
    {
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
        std::vector<int> me;
        std::vector<int> AI;
        std::vector<int> slot;
        for (size_t i = 0; i < 10; ++i)
        {
            me.push_back(numbers[i]);
            AI.push_back(numbers[i + 10]);
        }
        for(size_t j=20;j<=23;j++)
        {
            slot.push_back(numbers[j]);
        }
        std::sort(me.begin(),me.end());
        std::sort(AI.begin(),AI.end());
        return ThreeUnion(me,AI,slot);

    }
    FiveUnion Init1v3()
    {
        quint32 seed = static_cast<quint32>(QDateTime::currentMSecsSinceEpoch());
        QRandomGenerator random(seed);
        int lowerBound = 1;
        int upperBound = 104;

        std::vector<int> numbers;
        for (int i = lowerBound; i <= upperBound; ++i)
        {
            numbers.push_back(i);
        }
        for (int i = numbers.size() - 1; i > 0; --i)
        {
            int j = random.bounded(i + 1);
            int tmp = numbers[i];
            numbers[i] = numbers[j];
            numbers[j] = tmp;
        }
        std::vector<int> A;
        std::vector<int> B;
        std::vector<int> C;
        std::vector<int> D;
        std::vector<int> slot;
        for (size_t i = 0; i < 10; ++i)
        {
            A.push_back(numbers[i]);
            B.push_back(numbers[i + 10]);
            C.push_back(numbers[i + 20]);
            D.push_back(numbers[i + 30]);
        }
        for(size_t j=40;j<=43;j++)
        {
            slot.push_back(numbers[j]);
        }
        std::sort(A.begin(),A.end());
        std::sort(B.begin(),B.end());
        std::sort(C.begin(),C.end());
        std::sort(D.begin(),D.end());
        return FiveUnion(A,B,C,D,slot);
    }
}
#endif // GIVECARDALGORITHM_H
