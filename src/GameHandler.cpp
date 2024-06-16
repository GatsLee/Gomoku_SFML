#include <GameHandler.hpp>

/**
 * @brief constructor for local mode
 * 
 */
GameHandler::GameHandler(GameHandler::eGameRule rule, \
                         GameHandler::ePlayMode mode)
    : mTurn(BLACK_TURN)
    , mRule(rule)
    , mMode(mode)
    , mStatus(GAME_ONGOING)
    , mBannedMove(POSSIBLE)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            mBoard[i][j] = 0;
        }
    }
    mAI = nullptr;
}

/**
 * @brief constructor for AI mode
 * 
 */
GameHandler::GameHandler(GameHandler::eGameRule rule, \
                         GameHandler::ePlayMode mode, \
                         int aiTurn)
    : mTurn(BLACK_TURN)
    , mRule(rule)
    , mMode(mode)
    , mStatus(GAME_ONGOING)
    , mBannedMove(POSSIBLE)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            mBoard[i][j] = 0;
        }
    }
    //aiTurn: 1(BLACK_TURN) or 2(WHITE_TURN)
    mAI = new AIMinMax(aiTurn);
}

GameHandler::~GameHandler()
{}

bool GameHandler::IsOpenThree(int x, int y, std::pair<int, int> dir, eTurn turn)
{
    // suppose that mBoard[y][x] is the stone to be placed: not placed yet(0)
    int color = (turn == BLACK_TURN) ? BLACK_STONE : WHITE_STONE;
    int opponent = (turn == BLACK_TURN) ? WHITE_STONE : BLACK_STONE;
    int dx = dir.first, dy = dir.second;

    // check the nearest place: no opponent stone
    if ((IsPossibleMove(x + dx, y + dy) && mBoard[y + dy][x + dx] == opponent) && \
        (IsPossibleMove(x - dx, y - dy) && mBoard[y - dy][x - dx] == opponent))
        return false;
    // check possible open three
    for (auto pattern : openThree)
    {
        // check whether the pattern is applicable: check the edge & return the start point(else, return -16)
        int start = IsPossiblePattern(pattern, x, y, dx, dy);
        if (start == -16)
            continue;
        // check the pattern
        int patternCount = 0;
        int end =  start + pattern.size();
        for (int i = 0; start < end; start++, i++)
        {
            if ( ( (pattern[i] == 0 || pattern[i] == 3) && mBoard[y + dy * start][x + dx * start] == 0 ) \
                || (pattern[i] == 1 && mBoard[y + dy * start][x + dx * start] == color) )
            {
                patternCount++;
            }
            else
            {
                break;
            }
        }
        if (patternCount == pattern.size())
        {
            return true;
        }
    }
    return false;
}

int GameHandler::IsPossiblePattern(const std::vector<int>& pattern, int x, int y, int dx, int dy)
{
    int loc = 0;
    for (int i = 0; i < pattern.size(); ++i)
    {
        if (pattern[i] == 3)
        {
            loc = i;
            break;
        }
    }
    int start = -1 * loc;
    int end = pattern.size() - loc;
    if (IsPossibleMove(x + dx * start, y + dy * start) && \
        IsPossibleMove(x + dx * end, y + dy * end))
        return start;
    return -16;
}

int GameHandler::IsFourStone(int x, int y, std::pair<int, int> dir, eTurn turn)
{
    // suppose that mBoard[y][x] is the stone to be placed: not placed yet(0)
    int count = 0;
    int color = (turn == BLACK_TURN) ? BLACK_STONE : WHITE_STONE;
    int dx = dir.first, dy = dir.second;
    std::pair<int, int> start = {-1, -1};
    for (int i = -4; i <= 0; ++i)
    {
        int blank = 0, stone = 0;
        // check the scope(5stones: consist of 2 blank space && 3 same color stones)
        for (int j = 0; j < 5; ++j)
        {
            if (IsPossibleMove(x + dx * (i + j), y + dy * (i + j)))
            {
                if (mBoard[y + dy * (i + j)][x + dx * (i + j)] == 0)
                {
                    blank++;
                }
                else if (mBoard[y + dy * (i + j)][x + dx * (i + j)] == color)
                {
                    stone++;
                    if (stone == 1)
                    {
                        if (start != std::make_pair(x + dx * (i + j), y + dy * (i + j)))
                        {
                            start = std::make_pair(x + dx * (i + j), y + dy * (i + j));
                        }
                        else
                        {
                            stone = 0;
                        }
                    }
                }
                else
                {
                    continue;
                }
            }
        }
        if (blank == 2 && stone == 3)
        {
            count++;
        }
    }
    return count;
}

bool GameHandler::IsLegalMove(int x, int y)
{
    if (mStatus != GAME_ONGOING)
        return false;
    if (mBoard[y][x] != 0)
        return false;
    return true;
}

bool GameHandler::IsPossibleMove(int x, int y)
{
    if (mStatus != GAME_ONGOING)
        return false;
    if (x < 0 || x >= BOARD_SIZE \
        || y < 0 || y >= BOARD_SIZE)
        return false;
    return true;
}

bool GameHandler::CheckRule(int x, int y)
{
    const std::vector<std::pair<int, int> > directions = { {1, 0}, {0, 1}, \
                                                            {1, 1}, {1, -1}};
    int threeCount = 0;
    int fourCount = 0;

    if (mRule == RULE_FREESTYLE)
        return true;
    else if (mRule == RULE_STANDARD)
    {
        for (const auto& dir : directions)
        {
            if (IsOpenThree(x, y, dir, mTurn))
                threeCount++;
        }
        if (threeCount >= 2)
        {
            mBannedMove = OPEN_THREE;
            return false;
        }
    }
    else
    {
        for (const auto& dir : directions)
        {
            if (IsOpenThree(x, y, dir, mTurn))
                threeCount++;
            fourCount += IsFourStone(x, y, dir, mTurn);
        }
        if (mTurn == BLACK_TURN \
            && (threeCount >= 2 || fourCount >= 2))
        {
            mBoard[y][x] = static_cast<int>(mTurn);
            if (IsGameEnd() && mStatus == GAME_BLACK_WIN)
            {
                mStatus = GAME_ONGOING;
                mBoard[y][x] = 0;
                return true;
            }
            mBoard[y][x] = 0;
            if (threeCount >= 2)
                mBannedMove = OPEN_THREE;
            if (fourCount >= 2)
                mBannedMove = FOUR_FOUR;
            return false;
        }
    }
    return true;
}

bool GameHandler::PlaceStone(int x, int y)
{
    // check the legal move
    if (!IsLegalMove(x, y))
        return false;
    // place the stone: suppose that mBoard[y][x] is properly placed based on the rule
    mBoard[y][x] = mTurn;
    IsGameEnd();
    if (mTurn == BLACK_TURN)
    {
        mBlackStoneHistory.push_back(std::make_pair(x, y));
        mTurn = WHITE_TURN;
    }
    else
    {
        mWhiteStoneHistory.push_back(std::make_pair(x, y));
        mTurn = BLACK_TURN;
    }
    return true;
}

bool GameHandler::IsGameEnd()
{
    const int directions[8][2] = {{1, 0}, {-1, 0}, \
                                {0, 1}, {0, -1}, \
                                {1, 1}, {-1, -1}, \
                                {1, -1}, {-1, 1}};
    bool isFull = true;

    // check if the board is a draw
    for (int y = 0; y < BOARD_SIZE; ++y)
    {
        for (int x = 0; x < BOARD_SIZE; ++x)
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
        mStatus = GAME_DRAW;
        return true;
    }

    // check if the game is finished
    for (int y = 0; y < BOARD_SIZE; ++y)
    {
        for (int x = 0; x < BOARD_SIZE; ++x)
        {
            if (mBoard[y][x] != 0)
            {
                int color = mBoard[y][x];
                for (const auto& dir : directions)
                {
                    int count = 1;

                    int dx = dir[0], dy = dir[1];
                    int nx = x + dx, ny = y + dy;
                    
                    while (nx >= 0 && nx < BOARD_SIZE && ny >= 0 && ny < BOARD_SIZE &&
                           mBoard[ny][nx] == color)
                    {
                        ++count;
                        nx += dx;
                        ny += dy;
                    }
                    if (count >= 5 && CheckWin(count, color))
                        return true;
                }
            }
        }
    }
    return false;
}

bool GameHandler::CheckWin(int count, int color)
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

void GameHandler::ResetGameHandler()
{
    mTurn = BLACK_TURN;
    mStatus = GAME_ONGOING;
    mBannedMove = POSSIBLE;
    mBlackStoneHistory.clear();
    mWhiteStoneHistory.clear();
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            mBoard[i][j] = 0;
        }
    }
}

std::vector<std::pair<int, int> > GameHandler::GetBlackStoneHistory() const
{
    return mBlackStoneHistory;
}

std::vector<std::pair<int, int> > GameHandler::GetWhiteStoneHistory() const
{
    return mWhiteStoneHistory;
}

GameHandler::eTurn GameHandler::GetTurn() const
{
    return mTurn;
}

GameHandler::eTurn GameHandler::GetAITurn() const
{
    return mAIMinMax->GetAITurn();
}

GameHandler::eGameStatus GameHandler::GetGameStatus() const
{
    return mStatus;
}

GameHandler::eBannedMove GameHandler::GetBannedMove() const
{
    return mBannedMove;
}

void GameHandler::SetBannedMove(eBannedMove bannedMove)
{
    mBannedMove = bannedMove;
}

// for AI game
void GameHandler::UpdateAIBoard(int x, int y)
{
    mAI->UpdateBoard(x, y);
}

void GameHandler::CalculateAIMove()
{
    auto startTime = std::chrono::high_resolution_clock::now();
    mAI->CalculateAIMove();
    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = endTime - startTime;
    mTimeUsedToCalculate = duration.count();
}

double GameHandler::GetTimeUsedToCalculate()
{
    return mTimeUsedToCalculate;
}

std::pair<int, int> GameHandler::GetAIMove()
{
    if (mAI->IsCalculated())
        return mAI->GetBestMove();
    else
        return std::make_pair(-1, -1);
}

bool GameHandler::IsCalculated()
{
    return mAI->IsCalculated();
}