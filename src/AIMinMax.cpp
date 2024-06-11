#include <AIMinMax.hpp>

AIMinMax::AIMinMax(int turn, int board)
    : mAiTurn(turn)
    , mStartPoint(std::make_pair(-1, -1))
    , mAnsPoint(std::make_pair(-1, -1))
{
    mPossiblePoints.clear();
    mPossiblePoints.shrink_to_fit();
}

AIMinMax::~AIMinMax()
{}

int AIMinMax::GetAiTurn() const
{
    return mAiTurn;
}

void AIMinMax::Init()
{

}