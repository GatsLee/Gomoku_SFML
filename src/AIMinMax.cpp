#include <AIMinMax.hpp>
#include <iostream>

bool AIMinMax::cmpWeight(struct sCoor a, struct sCoor b)
{
    return a.weight > b.weight;
}

AIMinMax::AIMinMax(int AITurn)
{
    mTurn[0] = (AITurn == 1) ? 2 : 1; // player
    mTurn[1] = AITurn; // AI
    mBoard.resize(15, std::vector<int>(15, 0));
    mIsCalculated = false;
    mIsFirstMove = false;
}

AIMinMax::~AIMinMax()
{}

void AIMinMax::UpdateBoard(int x, int y, bool isAI)
{
    std::cout << "Update AI board" << std::endl;
    if (isAI == true) // AI
    {
        std::cout << "AI: " << x << " " << y << std::endl;
        mBoard[x][y] = mTurn[1];
    }
    else // player
    {
        std::cout << "Player: " << x << " " << y << std::endl;
        mBoard[x][y] = mTurn[0];
    }
}

std::deque < std::pair<int, int> > AIMinMax::FindPossibleMove(std::vector< std::vector<int> > curBoard)
{
    std::deque < std::pair<int, int> > possibleMove;
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (curBoard[i][j] > 0) continue;
                
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
                if (j < 14)
                {
                    if (curBoard[i - 1][j + 1] != 0
                        || curBoard[i][j + 1] != 0)
                    {
                        possibleMove.push_back(std::make_pair(i, j));
                        continue;
                    }
                }
                if (curBoard[i - 1][j] != 0)
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
                if (j < 14)
                {
                    if (curBoard[i + 1][j + 1] != 0
                        || curBoard[i][j + 1] != 0)
                    {
                        possibleMove.push_back(std::make_pair(i, j));
                        continue;
                    }
                }
                if (curBoard[i + 1][j] != 0)
                {
                    possibleMove.push_back(std::make_pair(i, j));
                    continue;
                }
            }
        }
    }
    return possibleMove;
}

void AIMinMax::CalculateWeight(std::vector< std::vector<int> > curBoard, int i, int j, bool forBlack, bool isAITurn, tCount &count)
{
    if (curBoard[i][j] == ((isAITurn) ? mTurn[1] : mTurn[0]))
    {
        count.consecutive++;
    }
    else if (curBoard[i][j] == 0)
    {
        if (count.consecutive > 0)
        {
            count.block--;
            count.weight += CalculateConsecutiveWeight(count.consecutive, count.block, isAITurn);
            count.consecutive = 0;
        }
        count.block = 1;
    }
    else if (count.consecutive > 0)
    {
        count.weight += CalculateConsecutiveWeight(count.consecutive, count.block, isAITurn);
        count.consecutive = 0;
        count.block = 2;
    }
    else
    {
        count.block = 2;
    }
}

void AIMinMax::CalculatedAftermath(tCount &count, bool forBlack, bool isAITurn)
{
    if (count.consecutive > 0)
    {
        count.weight += CalculateConsecutiveWeight(count.consecutive, count.block, isAITurn);
    }
    count.consecutive = 0;
    count.block = 0;
}

double AIMinMax::CalculateConsecutiveWeight(int consecutive, int block, bool isAITurn)
{
    double winGuarantee = 1000000.0;

    if (block == 2 && consecutive < 5) return 0;

    switch(consecutive)
    {
        case 5 :
            return 100000000.0;
        case 4 :
        {
            if (isAITurn)
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
                if (isAITurn)
                {
                    return 50000.0;
                }
                else
                {
                    return 50.0;
                }
            }
            else
            {
                if (isAITurn)
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
                if (isAITurn)
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
    return 200000000;
}

double AIMinMax::CalculateHorizontalScore(std::vector<std::vector<int> > curBoard, bool forBlack, bool isAITurn)
{
    tCount count = {0,0,2};

    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            CalculateWeight(curBoard, i, j, forBlack, isAITurn, count);
        }
        CalculatedAftermath(count, forBlack, isAITurn);
    }
    return count.weight;
}

double AIMinMax::CalculateVerticalScore(std::vector<std::vector<int> > curBoard, bool forBlack, bool isAITurn)
{
    tCount count = {0,0,2};

    for (int j = 0; j < 15; j++)
    {
        for (int i = 0; i < 15; i++)
        {
            CalculateWeight(curBoard, i, j, forBlack, isAITurn, count);
        }
        CalculatedAftermath(count, forBlack, isAITurn);
    }
    return count.weight;
}

double AIMinMax::CalculateDiagonalScore(std::vector<std::vector<int> > curBoard, bool forBlack, bool isAITurn)
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
            CalculateWeight(curBoard, i, j, forBlack, isAITurn, count);
        }
        CalculatedAftermath(count, forBlack, isAITurn);
    }

    // left bottom to right top
    for (int k = -14; k < 15; k++)
    {
        int iStart = std::max(0, k);
        int iEnd = std::min(14, k + 14);
        for (int i = iStart; i <= iEnd; i++)
        {
            int j = i - k;
            CalculateWeight(curBoard, i, j, forBlack, isAITurn, count);
        }
        CalculatedAftermath(count, forBlack, isAITurn);
    }
    return count.weight;
}

double AIMinMax::GetScore(std::vector< std::vector<int> >curBoard, bool forBlack, bool isAITurn)
{
    return CalculateHorizontalScore(curBoard, forBlack, isAITurn) \
                + CalculateVerticalScore(curBoard, forBlack, isAITurn) \
                + CalculateDiagonalScore(curBoard, forBlack, isAITurn);
}

double AIMinMax::EvaluateCurBoard(std::vector< std::vector<int> >curBoard, bool isAITurn)
{
    double blackScore = GetScore(curBoard, true, isAITurn);
    double whiteScore = GetScore(curBoard, false, isAITurn);

    double blackCalculated, whiteCalculated;
    double tmpBlack, tmpWhite;

    if (blackScore == 0) tmpBlack = 1.0;
    else tmpBlack = blackScore;

    if (whiteScore == 0) tmpWhite = 1.0;
    else tmpWhite = whiteScore;
    
    blackCalculated = blackScore / tmpWhite;
    whiteCalculated = whiteScore / tmpBlack;

    if (isAITurn)
    {
        if (mTurn[1] == 1)
            return blackCalculated;
        else
            return whiteCalculated;
    }
    else
    {
        if (mTurn[0] == 1)
            return blackCalculated;
        else
            return whiteCalculated;
    }
}

/**
 * @brief Search the best move for AI & the worst move for player
 * 
 * @param depth current depth
 * @param isMax whether it is AI's turn or not
 * @param alpha 
 * @param beta 
 * @return AIMinMax::tCoor 
 */
AIMinMax::tCoor AIMinMax::SearchBestMove(std::vector < std::vector<int> >curBoard, int depth, bool isMax, double alpha, double beta)
{
    if (depth == MAX_DEPTH)
    {
        return {-1,-1, EvaluateCurBoard(curBoard, !isMax)};
    }

    std::deque< std::pair<int, int> > possibleMove = FindPossibleMove(curBoard);

    if (possibleMove.empty())
    {
        return {-1, -1, EvaluateCurBoard(curBoard, !isMax)};
    }

    std::cout << "Possible move: " << possibleMove.size() << std::endl;
    std::cout << "Depth: " << depth << std::endl;

    tCoor bestMove = {-1, -1, (isMax) ? -1.0 : 100000000.0};
    if (isMax == true) // maximize the score of AI move
    {
        for (auto move : possibleMove)
        {
            curBoard[move.first][move.second] = mTurn[1]; // AI
            tCoor curMove = SearchBestMove(curBoard, depth + 1, false, alpha, beta);
            curMove.x = move.first;
            curMove.y = move.second;

            curBoard[move.first][move.second] = 0;

            if (curMove.weight > alpha)
            {
                alpha = curMove.weight;
            }
            if (curMove.weight >= beta)
                return curMove;
            if (curMove.weight > bestMove.weight)
            {
                bestMove = curMove;
            }
        }
    }
    else // minimize the score of player move
    {
        for (auto move : possibleMove)
        {
            curBoard[move.first][move.second] = mTurn[0]; // player
            tCoor curMove = SearchBestMove(curBoard, depth + 1, true, alpha, beta);
            curMove.x = move.first;
            curMove.y = move.second;

            curBoard[move.first][move.second] = 0;

            if (curMove.weight < beta)
            {
                beta = curMove.weight;
            }
            if (curMove.weight <= alpha)
                return curMove;
            if (curMove.weight < bestMove.weight)
            {
                bestMove = curMove;
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
    std::cout << "AI is calculating the best move" << std::endl;
    // if the board is empty(AI turn is black), set the first point to the center
    if (mTurn[1] == 1 && mIsFirstMove == false)
    {
        mCurBestMove = std::make_pair(7, 7);
        mIsCalculated = true;
        mIsFirstMove = true;
        return;
    }
    std::cout << "AI is calculating the best move2" << std::endl;
    // if the board is not empty, calculate the best move
    // if there is a move that can finish the game, do it
    tCoor finMove = SearchFinishingMove();

    if (finMove.weight != -1.0)
    {
        std::cout << "AI is calculating the finishing move" << std::endl;
        mIsCalculated = true;
        return;
    }
    else // if there is no move that can finish the game, calculate the best move
    {
        std::cout << "AI is calculating the best move3" << std::endl;
        tCoor tmp = SearchBestMove(mBoard, 0, true, -1.0, 10000000.0);  
        mCurBestMove = std::make_pair(tmp.x, tmp.y);
        mIsCalculated = true;
        std::cout << "AI is calculating the best move4" << std::endl;
        return;
    }
}

AIMinMax::tCoor AIMinMax::SearchFinishingMove()
{
    tCoor bestMove = {-1, -1, -1.0};
    std::deque < std::pair<int, int> > possibleMove = FindPossibleMove(mBoard);

    for (auto move : possibleMove)
    {
        mBoard[move.first][move.second] = mTurn[1]; // AI
        double score = EvaluateCurBoard(mBoard, mTurn[1] == 1 ? true : false);
        mBoard[move.first][move.second] = 0;

        if (score >= 100000000.0)
        {
            bestMove.x = move.first;
            bestMove.y = move.second;
            bestMove.weight = score;
            break;
        }
    }
    return bestMove;
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

void AIMinMax::SetCalculated(bool isCalculated)
{
    mIsCalculated = isCalculated;
}

void AIMinMax::ResetCalculation()
{
   SetCalculated(false);
   mCurBestMove = std::make_pair(-1, -1);
   mSavePos.clear();
   mPossiblePoints.clear();
}
