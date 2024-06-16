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

    typedef struct sCount
    {
        int weight;
        int emptySpace;
        int enemy;
    } tCount;
    typedef struct sCoor
    {
        int x;
        int y;
        int weight;
    } tCoor;

public:
    AIMinMax(int turn);
    ~AIMinMax();

    void Init();

    void CalculateAIMove(); // main function
    void UpdateBoard(int x, int y);
    void SetWeight();
    void FindPossiblePoints();
    void SearchBestMove(int depth);

    std::pair<int, int> GetBestMove() const;
    void SetBestMove(int x, int y);
    bool cmpWeight(struct sCoor &a, struct sCoor &b);

private:
    const int dir[8][2] = {
        {0, 1}, {1, 0}, {1, 1}, {1, -1}, \
        {0, -1}, {-1, 0}, {-1, -1}, {-1, 1}
    };

private:
    int mTurn[2]; // first: player, second: AI
    int mBoard[15][15];
    int mWeight[15][15];
    int w2[2][6][3][2]; // 2: player, AI, 6: num, 3: 2, 3, 4, 5, 6, 7, 2: 2, 3

    std::pair<int, int> mStartPoint;
    std::pair<int, int> mAnsPoint;
    std::pair<int, int> mCurBestMove;

    std::deque< tCoor > mSavePos;
    std::deque< std::pair<int, int> > mPossiblePoints;
};