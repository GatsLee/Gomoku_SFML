#pragma once

#include <deque>
#include <climits>

#include <GameHandler.hpp>

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
    AIMinMax(GameHandler::eTurn turn);
    ~AIMinMax();

    void Init();

    GameHandler::eTurn GetAiTurn() const;

private:
    GameHandler::eTurn mAiTurn;

    std::pair<int, int> mStartPoint;
    std::pair<int, int> mAnsPoint;

    std::deque< std::pair<int, int> > mPossiblePoints;

};