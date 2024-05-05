#include <GameHandler.hpp>

GameHandler::GameHandler(GameHandler::eGameRule rule, \
                         GameHandler::ePlayMode mode, \
                         eAIType aiType)
    : mTurn(BLACK_TURN)
    , mRule(rule)
    , mMode(mode)
    , mStatus(GAME_ONGOING)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            mBoard[i][j] = 0;
        }
    }
    if (aiType == AI_NOTDEFINED)
        mAI = nullptr;
    else
        mAI = nullptr;
}

GameHandler::~GameHandler()
{
    if (mAI != nullptr)
    {
        delete mAI;
        mAI = nullptr;
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



bool GameHandler::IsLegalMove(int x, int y)
{
    if (mStatus != GAME_ONGOING)
        return false;
    if (mBoard[y][x] != 0)
        return false;
    return true;
}

bool GameHandler::PlaceStone(int x, int y)
{
    if (mStatus != GAME_ONGOING)
        return false;
    // based on free style rule: no limitation on the stone placement
    if (mBoard[y][x] != 0)
        return false;
    mBoard[y][x] = mTurn;
    IsGameEnd();
    if (mTurn == BLACK_TURN)
    {
        std::cout << "Black turn" << std::endl;
        mBlackStoneHistory.push_back(std::make_pair(x, y));
        mTurn = WHITE_TURN;
    }
    else
    {
        std::cout << "White turn" << std::endl;
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
                    if (count == 5)
                    {
                        mStatus = (color == BLACK_STONE) ? GAME_BLACK_WIN : GAME_WHITE_WIN;
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

GameHandler::eTurn GameHandler::GetTurn() const
{
    return mTurn;
}

GameHandler::eGameStatus GameHandler::GetGameStatus() const
{
    return mStatus;
}