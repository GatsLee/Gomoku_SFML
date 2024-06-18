#include <AIMinMax.hpp>

bool AIMinMax::cmpWeight(struct sCoor a, struct sCoor b)
{
    return a.weight > b.weight;
}

AIMinMax::AIMinMax(int AITurn)
    : mStartPoint(std::make_pair(-1, -1))
    , mAnsPoint(std::make_pair(-1, -1))
{
    mTurn[0] = (AITurn == 1) ? 2 : 1; // player
    mTurn[1] = AITurn; // AI
    mIsCalculated = false;
}

AIMinMax::~AIMinMax()
{}

void AIMinMax::UpdateBoard(int x, int y)
{
    mBoard[x][y] = mTurn[0]; // player
}

std::deque < std::pair<int, int> > AIMinMax::FindPossibleMove(std::vector< std::vector<int> > curBoard)
{
    std::deque < std::pair<int, int> > possibleMove;
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (curBoard[i][j] == 0)
            {
                if (i > 0)
                {
                    if (j > 0)
                    {
                        if (curBoard[i - 1][j - 1] != 0
                            || curBoard[i][j - 1] != 0)
                        {
                            possibleMove.push_back(std::make_pair(i, j));
                            continue;
                        }
                    }
                    else if ( j < 14)
                    {
                        if (curBoard[i - 1][j + 1] != 0
                            || curBoard[i][j + 1] != 0)
                        {
                            possibleMove.push_back(std::make_pair(i, j));
                            continue;
                        }
                    }
                    else if (curBoard[i - 1][j] != 0)
                    {
                        possibleMove.push_back(std::make_pair(i, j));
                        continue;
                    }
                }
                else if (i < 14)
                {
                    if (j > 0)
                    {
                        if (curBoard[i + 1][j - 1] != 0
                            || curBoard[i][j - 1] != 0)
                        {
                            possibleMove.push_back(std::make_pair(i, j));
                            continue;
                        }
                    }
                    else if (j < 14)
                    {
                        if (curBoard[i + 1][j + 1] != 0
                            || curBoard[i][j + 1] != 0)
                        {
                            possibleMove.push_back(std::make_pair(i, j));
                            continue;
                        }
                    }
                    else if (curBoard[i + 1][j] != 0)
                    {
                        possibleMove.push_back(std::make_pair(i, j));
                        continue;
                    }
                }
            }
        }
    }
    return possibleMove;
}

void AIMinMax::CalculateWeight(std::vector< std::vector<int> > curBoard, int i , int j, bool isMax, int curTurn, tCount &count)
{
    if (curBoard[i][j] == ((curTurn == mTurn[1]) ? 2 : 1))
    {
        count.consecutive++;
    }
    else if (curBoard[i][j] == 0)
    {
        if (count.consecutive > 0)
        {
            count.block--;
            count.weight += CalculateConsecutiveWeight(count.consecutive, count.block, isMax, curTurn);
            count.consecutive = 0;
        }
        count.block = 1;
    }
    else if (count.consecutive > 0)
    {
        count.weight += CalculateConsecutiveWeight(count.consecutive, count.block, isMax, curTurn);
        count.consecutive = 0;
        count.block = 2;
    }
    else
    {
        count.block = 2;
    }
}

void AIMinMax::CalculatedAftermath(tCount &count,bool isMax, int curTurn)
{
    if (count.consecutive > 0)
    {
        count.weight += CalculateConsecutiveWeight(count.consecutive, count.block, isMax, curTurn);
    }
    count.consecutive = 0;
    count.block = 0;
}

double AIMinMax::CalculateConsecutiveWeight(int consecutive, int block, bool isMax, int curTurn)
{
    double winGuarantee = 1000000.0;

    if (block == 2 && consecutive < 5) return 0;

    switch(consecutive)
    {
        case 5 :
            return 1000000000.0;
        case 4 :
        {
            if (curTurn == mTurn[1])
            {
                return winGuarantee;
            }
            else
            {
                if (block == 0)
                {
                    return winGuarantee / 4;
                }
                else
                {
                    return 200.0;
                }
            }
        };
        case 3 :
        {
            if (block == 0)
            {
                if (curTurn == mTurn[1])
                {
                    return 300.0;
                }
                else
                {
                    return 50.0;
                }
            }
            else
            {
                if (curTurn == mTurn[1])
                {
                    return 7.0;
                }
                else
                {
                    return 5.0;
                }
            }
        };
        case 2 :
        {
            if (block == 0)
            {
                if (curTurn == mTurn[1])
                {
                    return 7.0;
                }
                else
                {
                    return 5.0;
                }
            }
            else
            {
                return 3.0;
            }
        };
        case 1 :
        {
            return 1;
        };
    }
    return 0;
}

double AIMinMax::CalculateHorizontalScore(std::vector<std::vector<int> > curBoard, bool isMax, int curTurn)
{
    tCount count = {0,0,2};

    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            CalculateWeight(curBoard, i, j, isMax, curTurn, count);
        }
        CalculatedAftermath(count, isMax, curTurn);
    }
    return count.weight;
}

double AIMinMax::CalculateVerticalScore(std::vector<std::vector<int> > curBoard, bool isMax, int curTurn)
{
    tCount count = {0,0,2};

    for (int j = 0; j < 15; j++)
    {
        for (int i = 0; i < 15; i++)
        {
            CalculateWeight(curBoard, i, j, isMax, curTurn, count);
        }
        CalculatedAftermath(count, isMax, curTurn);
    }
    return count.weight;
}

double AIMinMax::CalculateDiagonalScore(std::vector<std::vector<int> > curBoard, bool isMax, int curTurn)
{
    tCount count = {0,0,2};

    // left top to right bottom
    for (int k = 0; k <= 28; k++)
    {
        int iStart = std::max(0, k - 14);
        int iEnd = std::min(14, k);
        for (int i = iStart; i <= iEnd; i++)
        {
            int j = k - i;
            CalculateWeight(curBoard, i, j, isMax, curTurn, count);
        }
        CalculatedAftermath(count, isMax, curTurn);
    }

    // left bottom to right top
    for (int k = -14; k < 15; k++)
    {
        int iStart = std::max(0, k);
        int iEnd = std::min(14, k + 14);
        for (int i = iStart; i <= iEnd; i++)
        {
            int j = i - k;
            CalculateWeight(curBoard, i, j, isMax, curTurn, count);
        }
        CalculatedAftermath(count, isMax, curTurn);
    }
    return count.weight;
}

double AIMinMax::GetScore(std::vector< std::vector<int> >curBoard, bool isAI, int curTurn)
{
    return CalculateHorizontalScore(curBoard, isAI, curTurn) \
                + CalculateVerticalScore(curBoard, isAI, curTurn) \
                + CalculateDiagonalScore(curBoard, isAI, curTurn);
}

double AIMinMax::EvaluateCurBoard(std::vector< std::vector<int> >curBoard, bool isMax, int curTurn)
{
    double blackScore, whiteScore;
    if (curTurn == 1) // black
    {
        blackScore = GetScore(curBoard, true, curTurn);
        whiteScore = GetScore(curBoard, false, curTurn);
    }
    else
    {
        blackScore = GetScore(curBoard, false, curTurn);
        whiteScore = GetScore(curBoard, true, curTurn);
    }

    if (blackScore == 0) blackScore = 1.0;

    if (curTurn == 1)
    {
        return whiteScore / blackScore;
    }
    else
    {
        return blackScore / whiteScore;
    }
}

AIMinMax::tCoor AIMinMax::SearchBestMove(std::vector < std::vector<int> >curBoard, int depth, bool isMax, double alpha, double beta)
{
    if (depth == MAX_DEPTH)
    {
        return {-1,-1, EvaluateCurBoard(curBoard, !isMax, mTurn[1])};
    }

    std::deque< std::pair<int, int> > possibleMove = FindPossibleMove(curBoard);

    if (possibleMove.empty())
    {
        return {-1, -1, EvaluateCurBoard(curBoard, !isMax, mTurn[1])};
    }

    tCoor bestMove = {-1, -1, (isMax) ? -1.0 : 1.0};
    if (isMax == true) // maximize the score of AI move
    {
        for (auto move : possibleMove)
        {
            curBoard[move.first][move.second] = mTurn[1]; // AI
            tCoor curMove = SearchBestMove(curBoard, depth + 1, !isMax, alpha, beta);
            curMove.x = move.first;
            curMove.y = move.second;
            curBoard[move.first][move.second] = 0;

            if (curMove.weight > bestMove.weight)
            {
                bestMove = curMove;
            }
            alpha = std::max(alpha, bestMove.weight);
            if (beta <= alpha)
            {
                break;
            }
        }
    }
    else // minimize the score of player move
    {
        for (auto move : possibleMove)
        {
            curBoard[move.first][move.second] = mTurn[0]; // player
            tCoor curMove = SearchBestMove(curBoard, depth + 1, !isMax, alpha, beta);
            curMove.x = move.first;
            curMove.y = move.second;
            curBoard[move.first][move.second] = 0;

            if (curMove.weight < bestMove.weight)
            {
                bestMove = curMove;
            }
            beta = std::min(beta, bestMove.weight);
            if (beta <= alpha)
            {
                break;
            }
        }
    }
    return bestMove;
}

/**
 * @brief main function to calculate the AI move
 * 
 */
void AIMinMax::CalculateAIMove()
{
    // if the board is empty, set the first point to the center
    if (mStartPoint.first == -1 && mStartPoint.second == -1)
    {
        mCurBestMove = std::make_pair(7, 7);
        mStartPoint = mCurBestMove;
        mIsCalculated = true;
        return;
    }
    // if the board is not empty, calculate the best move
    // if there is a move that can finish the game, do it
    bool isEnd = SearchFinishingMove();

    if (isEnd == true)
    {
        mIsCalculated = true;
        return;
    }
    else // if there is no move that can finish the game, calculate the best move
    {
        tCoor tmp = SearchBestMove(mBoard, 0, true, 0.0, 0.0);  
        mCurBestMove = std::make_pair(tmp.x, tmp.y);
        mIsCalculated = true;
        return;
    }
}

bool AIMinMax::SearchFinishingMove()
{
    return IsGameEnd(mTurn[1]);
}

std::pair<int, int> AIMinMax::GetBestMove() const
{
    return mCurBestMove;
}

void AIMinMax::SetBestMove(int x, int y)
{
    mCurBestMove = std::make_pair(x, y);
}

bool AIMinMax::IsCalculated() const
{
    return mIsCalculated;
}

//clone function from game handler
bool AIMinMax::IsGameEnd(int curTurn)
{
    const int directions[8][2] = {{1, 0}, {-1, 0}, \
                                {0, 1}, {0, -1}, \
                                {1, 1}, {-1, -1}, \
                                {1, -1}, {-1, 1}};
    bool isFull = true;

    // check if the game is finished
    for (int y = 0; y < 15; ++y)
    {
        for (int x = 0; x < 15; ++x)
        {
            if (mBoard[y][x] == curTurn)
            {
                for (const auto& dir : directions)
                {
                    int count = 1;

                    int dx = dir[0], dy = dir[1];
                    int nx = x + dx, ny = y + dy;
                    
                    while (nx >= 0 && nx < 15 && ny >= 0 && ny < 15)
                    {
                        ++count;
                        nx += dx;
                        ny += dy;
                    }
                    if (count >= 5 && CheckWin(count, curTurn))
                        return true;
                }
            }
        }
    }
    return false;
}

bool AIMinMax::CheckWin(int count, int color)
{
    if (count == 5)
    {
        return true;
    }
    else
    {
        // if (mRule == RULE_FREESTYLE)
        // {
        //     return true;
        // }
        // else if (mRule == RULE_STANDARD)
        // {
        //     return false;
        // }
        // else if (mRule == RULE_RENJU)
        // {
        //     if (color == 2)
        //     {
        //         return true;
        //     }
        // }
        return false;
    }
}