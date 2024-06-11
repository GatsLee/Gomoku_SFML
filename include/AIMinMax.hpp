#pragma once

#include <deque>
#include <climits>

class AIMinMax
{
public:
    enum eWeight {
        ZER = 0,
        FIR = 1,
        SEC = 40,
        THR = 999,
        FOU = 1000000,
        FIV = INT_MAX,
    };

    struct sCoor
    {
        std::pair<int, int> XY;
        enum eWeight weight;
    };

public:
    AIMinMax(int turn);
    ~AIMinMax();

    void Init();

    int GetAiTurn() const;

private:
    int mAiTurn;

    std::pair<int, int> mStartPoint;
    std::pair<int, int> mAnsPoint;

    std::deque< std::pair<int, int> > mPossiblePoints;

};