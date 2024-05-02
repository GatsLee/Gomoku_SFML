#include "SFML/System/Vector2.hpp"
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

bool GameHandler::IsLegalMove(sf::Vector2i position)
{
    if (mStatus != GAME_ONGOING)
        return false;
    if (mBoard[position.x][position.y] != 0)
        return false;
    return true;
}

bool GameHandler::PlaceStone(sf::Vector2i position)
{
    if (mStatus != GAME_ONGOING)
        return false;
    // based on free style rule: no limitation on the stone placement
    if (mBoard[position.x][position.y] != 0)
        return false;
    mBoard[position.x][position.y] = mTurn;
    if (IsGameEnd())
        return true;
    if (mTurn == BLACK_TURN)
        mTurn = WHITE_TURN;
    else
        mTurn = BLACK_TURN;
    return true;
    // check the game status after placing the stone
}

bool GameHandler::IsGameEnd()
{
    const int directions[8][2] = {{1, 0}, {-1, 0}, \
                                {0, 1}, {0, -1}, \
                                {1, 1}, {-1, -1}, \
                                {1, -1}, {-1, 1}};
    bool isFull = true;

    // check if the board is a draw
    for (int x = 0; x < BOARD_SIZE; ++x)
    {
        for (int y = 0; y < BOARD_SIZE; ++y)
        {
            if (mBoard[x][y] == 0)
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
    for (int x = 0; x < BOARD_SIZE; ++x) {
        for (int y = 0; y < BOARD_SIZE; ++y) {
            if (mBoard[x][y] != 0)
            {
                int color = mBoard[x][y];

                for (const auto& dir : directions)
                {
                    int count = 1;

                    int dx = dir[0], dy = dir[1];
                    int nx = x + dx, ny = y + dy;
                    
                    while (nx >= 0 && nx < BOARD_SIZE && ny >= 0 && ny < BOARD_SIZE &&
                           mBoard[nx][ny] == color)
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

