#pragma once

#include <iostream>
#include <vector>

class IAI
{
public:
    IAI();
    virtual ~IAI();

    virtual void init() = 0;
    virtual void calculateMove() = 0;
    virtual void placeMove() = 0;

private:
    std::string mAlgoName;
    int mDepth;
    std::vector< std::pair<int, int> > mPossibleMoves;
    std::vector< std::pair<int, int> > mBestMoves;

    IAI &operator=(const IAI &rhs);
    IAI(const IAI &rhs);
};