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
    memset(highestWeight, 0, sizeof(highestWeight));
}

AIMinMax::~AIMinMax()
{}

/**
 * @brief update the board with the new point: player
 * 
 * @param x 
 * @param y 
 */
void AIMinMax::UpdateBoard(int x, int y)
{
    mBoard[x][y] = mTurn[0];
}

void AIMinMax::FindPossiblePoints()
{
    mPossiblePoints.clear();
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (mBoard[i][j] == 0 && mWeight[i][j] > 0)
            {
                mPossiblePoints.push_back(std::make_pair(i, j));
            }
        }
    }
}

double AIMinMax::CalculateHorizontalScore(std::vector<std::vector<int> > curBoard, bool isMax, int curTurn)
{
    
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

std::deque < std::pair<int, int> > AIMinMax::FindPossibleMove(std::vector < std::vector<int> >curBoard)
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
                        // check if there is a stone around the point
                        if (curBoard[i - 1][j - 1] != 0
                            || curBoard[i - 1][j] != 0)
                        {
                            possibleMove.push_back(std::make_pair(i, j));
                        }
                    }
                    else if (j < 14)
                    {
                        if (curBoard[i - 1][j] != 0
                            || curBoard[i - 1][j + 1] != 0)
                        {
                            possibleMove.push_back(std::make_pair(i, j));
                        }
                    }
                    else if (curBoard[i - 1][j] != 0)
                    {
                        possibleMove.push_back(std::make_pair(i, j));
                    }
                }
                else if (i < 14)
                {
                    if (j > 0)
                    {
                        if (curBoard[i][j - 1] != 0
                            || curBoard[i + 1][j - 1] != 0)
                        {
                            possibleMove.push_back(std::make_pair(i, j));
                        }
                    }
                    else if (j < 14)
                    {
                        if (curBoard[i][j+1] != 0
                            || curBoard[i + 1][j + 1] != 0)
                        {
                            possibleMove.push_back(std::make_pair(i, j));
                        }
                    }
                    else if (curBoard[i + 1][j] != 0)
                    {
                        possibleMove.push_back(std::make_pair(i, j));
                    }
                }
            }
        }
    }
    return possibleMove;
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
    if (isMax == true)
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
    else
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
        mCurBestMove = SearchBestMove(mBoard, 0, true, 0.0, 0.0);  
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
    return mTflag;
}

// clone functions for rule check(win, banned move, etc.) from GameHandler
bool AIMinMax::CheckWin(int count, int color)
{
    if (count == 5)
    {
        mStatus = (color == BLACK_STONE) ? GAME_BLACK_WIN : GAME_WHITE_WIN;
        return true;
    }
    else
    {
        if (mRule == RULE_FREESTYLE)
        {
            mStatus = (color == BLACK_STONE) ? GAME_BLACK_WIN : GAME_WHITE_WIN;
            return true;
        }
        else if (mRule == RULE_STANDARD)
        {
            return false;
        }
        else if (mRule == RULE_RENJU)
        {
            if (color == 2)
            {
                mStatus = GAME_WHITE_WIN;
                return true;
            }
        }
        return false;
    }
}

bool AIMinMax::IsGameEnd(int curTurn)
{
    const int directions[8][2] = {{1, 0}, {-1, 0}, \
                                {0, 1}, {0, -1}, \
                                {1, 1}, {-1, -1}, \
                                {1, -1}, {-1, 1}};
    bool isFull = true;

    // check if the board is a draw
    for (int y = 0; y < 15; ++y)
    {
        for (int x = 0; x < 15; ++x)
        {
            if (mBoard[y][x] == 0)
            {
                isFull = false;
                break;
            }
        }
    }
    if (isFull)
    {
        return true;
    }

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
                    
                    while (nx >= 0 && nx < 15 && ny >= 0 && ny < 15 &&
                           mBoard[ny][nx] == curTurn)
                    {
                        ++count;
                        nx += dx;
                        ny += dy;
                    }
                    if (count >= 5 && CheckWin(count, curTurn))
                    {
                        if (curTurn == mTurn[1])
                        {
                            mCurBestMove = std::make_pair(x, y);
                        }
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
