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

void AIMinMax::Init()
{
	//0,2,25,421,1200000,10000000 },{ 0,1,22,105,17000,10000000
	// my or your / num / enemy / space
	//num=1 일때 빈공간 0인것만 1 나머지는 0
	//map[5][9] = 1; map[5][10] = 2; map[5][11] = 2; map[5][13] = 2; map[5][14] = 1;
	w2[0][1][0][0] = 2; w2[1][1][0][0] = 1;
	w2[0][1][0][1] = 2; w2[1][1][0][1] = 0;
	//num=2 일때
	w2[0][2][0][0] = 25, w2[1][2][0][0] = 4;
	w2[0][2][0][1] = 25, w2[1][2][0][1] = 1;
	w2[0][2][1][1] = 2; w2[1][2][1][1] = 1;
	w2[0][2][1][0] = 2; w2[1][2][1][0] = 1;
	

	//num=3
	w2[0][3][0][0] = 521, w2[1][3][0][0] = 105;
	w2[0][3][0][1] = 301; w2[1][3][0][1] = 13;	
	w2[0][3][1][0] = 301, w2[1][3][1][0] = 13;
	w2[0][3][1][1] = 301, w2[1][3][1][1] = 13;
	//num=4
	w2[0][4][0][0] = 21000; w2[0][4][1][0] = 20010; w2[0][4][2][0] = 20010;
	w2[1][4][0][0] = 4001; w2[1][4][1][0] = 4001; w2[1][4][2][0] = 4001;
}

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

void AIMinMax::SetWeight(int curTurn[2])
{
    memset(mWeight, 0, sizeof(mWeight));

    for (int type = 0; type < 2; type++)
    {
        for (int i = 0; i < 15; i++)
        {
            for (int j = 0; j < 15; j++)
            {
                int sum = 0;
                tCount count[4]; // 0: horizontal, 1: vertical, 2: diagonal, 3: anti-diagonal
                if (mBoard[i][j]) continue; // if the point is already occupied, skip
                for (int d = 0; d < 4; d++)
                {
                    int nx, ny;
                    int cnt = 1;
                    int zeroCnt = 0;
                    int zeroCnt1 = 0;
                    int remember = 0;
                    int zeroCnt2 = 0;
                    int num = 0;
                    int enemyCnt = 0;
                    int before;

                    // check the direction
                    while (true) {
						nx = i + (cnt * dir[d][0]), ny = j + (cnt * dir[d][1]);
						before = mBoard[nx - dir[d][0]][ny - dir[d][1]];
                        // if the point is out of the board
						if (nx < 0 || ny < 0 || nx >= 15 || ny >= 15)
                        {
							if (remember || zeroCnt1 == 0) {
								enemyCnt++;
							}
							if (before != 0)remember = zeroCnt1;

							break;
						}
                        // if the point is occupied by the enemy
						if (mBoard[nx][ny] == mTurn[(type + 1) % 2])
                        {
							if (remember || zeroCnt1 == 0) {
								enemyCnt++;
							}
							if (before != 0)remember = zeroCnt1;

							break;
						}
                        // if the point is occupied by the current one
						if (mBoard[nx][ny] == mTurn[type]) {
							remember = zeroCnt1;
							num++;
						}
                        // if the point is empty
						if (mBoard[nx][ny] == 0)zeroCnt1++;
                        // if the empty space is more than 2, break
						if (zeroCnt1 >= 2)break;
						cnt++;
					}
					zeroCnt1 = remember;
					cnt = 1;
					remember = 0;

                    // check the opposite direction
                    while (true)
                    {
                        nx = i + (cnt * dir[d + 4][0]), ny = j + (cnt * dir[d + 4][1]);
						if (nx < 0 || ny < 0 || nx >= 15 || ny >= 15)
                        {
							if (remember || zeroCnt2 == 0) {
								enemyCnt++;
							}
							if (before != 0)remember = zeroCnt2;
							break;
						}
						if (mBoard[nx][ny] == mTurn[(type + 1) % 2])
                        {
							if (remember || zeroCnt2 == 0) {
								enemyCnt++;
							}
							if (before != 0)remember = zeroCnt2;
							break;
						}

						if (mBoard[nx][ny] == mTurn[type])
                        {
							remember = zeroCnt2;
							num++;
						}
						if (mBoard[nx][ny] == 0)zeroCnt2++;
						if (zeroCnt2 >= 2) break;
						cnt++;
                    }
                    zeroCnt2 = remember;
                    zeroCnt = zeroCnt1 + zeroCnt2;
                    count[d] = {num, zeroCnt, enemyCnt};
                }

                for (int d = 0; d < 4; d++)
                {
                    int num = count[d].weight, enemy = count[d].enemy, emptyspace = count[d].emptySpace;
					int temp_w = w2[(type + 1) % 2][num][enemy][emptyspace];

					if (emptyspace >= 2 || num + emptyspace >= 5)continue;
					if (num != 4 && enemy >= 2)continue;
					sum += temp_w;
                }
                mWeight[i][j] += sum;
                if (mBoard[i][j]) mWeight[i][j] = 0;
            }
        }
    }
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
                possibleMove.push_back(std::make_pair(i, j));
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


    if (isMax == true)
    {

    }
    else
    {
    
    }
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
