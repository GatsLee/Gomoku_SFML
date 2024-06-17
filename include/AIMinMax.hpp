#pragma once

#include <deque>
#include <vector>
#include <climits>

#define MAX_DEPTH 30

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

    // 
    typedef struct sCoor
    {
        int x;
        int y;
        double weight;
    } tCoor;

public:
    AIMinMax(int AITurn);
    ~AIMinMax();

    void Init();

    void CalculateAIMove(); // main function
    void UpdateBoard(int x, int y);
    void SetWeight(int curTurn[2]);
    void FindPossiblePoints();
    

    std::deque < std::pair<int, int> > FindPossibleMove(std::vector < std::vector<int> >curBoard);
    double EvaluateCurBoard(std::vector< std::vector<int> > curBoard, bool isMax, int curTurn);
    bool SearchFinishingMove();
    tCoor SearchBestMove(std::vector< std::vector<int> > curBoard, int depth, bool isMax, double alpha, double beta);

    std::pair<int, int> GetBestMove() const;
    void SetBestMove(int x, int y);
    static bool cmpWeight(struct sCoor a, struct sCoor b);

    bool IsCalculated() const;

   // clone functions for rule check(win, banned move, etc.) from GameHandler
    bool CheckWin(int count, int color);
    bool IsGameEnd(int curTurn);

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
    int highestWeight[6];
    bool mIsCalculated;

    std::pair<int, int> mStartPoint;
    std::pair<int, int> mAnsPoint;
    std::pair<int, int> mCurBestMove;

    std::deque< tCoor > mSavePos;
    std::deque< std::pair<int, int> > mPossiblePoints;
};