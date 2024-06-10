#include <AIMinMax.hpp>

AIMinMax::AIMinMax(GameHandler::eTurn turn)
    : mStartPoint(std::make_pair(-1, -1))
    , mAnsPoint(std::make_pair(-1, -1))
{
    mPossiblePoints.clear();
    mPossiblePoints.shrink_to_fit();
}

AIMinMax::~AIMinMax()
{}

GameHandler::eTurn AIMinMax::GetAiTurn() const
{
    return mAiTurn;
}