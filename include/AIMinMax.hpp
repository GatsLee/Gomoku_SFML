#pragma once

#include <deque>
#include <vector>
#include <climits>
#include <cmath>

#define MAX_DEPTH 30

class AIMinMax final
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
        int consecutive;
        int block; // blocked by enemy or board border
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
    void FindPossiblePoints();


    double EvaluateCurBoard(std::vector< std::vector<int> > curBoard, bool isMax, int curTurn);
    std::deque < std::pair<int, int> > FindPossibleMove(std::vector< std::vector<int> > curBoard);
    bool SearchFinishingMove();
    tCoor SearchBestMove(std::vector< std::vector<int> > curBoard, int depth, bool isMax, double alpha, double beta);

    double GetScore(std::vector< std::vector<int> >curBoard, bool isAI, int curTurn);

    double CalculateConsecutiveWeight(int consecutive, int block, bool isMax, int curTurn);
    void CalculateWeight(std::vector< std::vector<int> > curBoard, int i , int j, bool isMax, int curTurn, tCount &count);
    void CalculatedAftermath(tCount &count,bool isMax, int curTurn);

    double CalculateHorizontalScore(std::vector< std::vector<int> > curBoard, bool isMax, int curTurn);
    double CalculateVerticalScore(std::vector< std::vector<int> > curBoard, bool isMax, int curTurn);
    double CalculateDiagonalScore(std::vector< std::vector<int> > curBoard, bool isMax, int curTurn);
    
    std::pair<int, int> GetBestMove() const;
    void SetBestMove(int x, int y);
    static bool cmpWeight(struct sCoor a, struct sCoor b);

    bool IsCalculated() const;

    // clone functions from game handler
    bool IsGameEnd(int curTurn);
    bool CheckWin(int count, int color);

private:
    int mTurn[2]; // first: player, second: AI
    std::vector< std::vector <int> > mBoard;
    bool mIsCalculated;

    std::pair<int, int> mStartPoint;
    std::pair<int, int> mAnsPoint;
    std::pair<int, int> mCurBestMove;

    std::deque< tCoor > mSavePos;
    std::deque< std::pair<int, int> > mPossiblePoints;
};