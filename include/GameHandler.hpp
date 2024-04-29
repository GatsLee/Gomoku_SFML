#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <IAI.hpp>
#include <AScene.hpp>

class GameHandler
{
public:
    enum eTurn
    {
        BLACK_TURN = 0,
        WHITE_TURN = 1,
    };

    enum eGameUnit
    {
        BLACK_STONE = 1,
        WHITE_STONE = 2,
        BOARD_SIZE = 15,
        MAX_STONE = 225,
    };

    enum eGameRule
    {
        RULE_FREESTYLE,
        RULE_STANDARD,
        RULE_RENJU,
    };

    enum eGameStatus
    {
        GAME_ONGOING,
        GAME_WHITE_WIN,
        GAME_BLACK_WIN,
        GAME_DRAW,
    };

    enum ePlayMode
    {
        MODE_LOCAL,
        MODE_AI,
    };

    enum eAIType
    {
        AI_NOTDEFINED,
        AI_RANDOM,
        AI_MINIMAX,
        AI_MCTS,
    };

public:
    GameHandler(GameHandler::eGameRule rule, \
                GameHandler::ePlayMode mode, \
                eAIType aiType);
    ~GameHandler();

    bool PlaceStone(sf::Vector2i position);
    bool IsGameEnd();

private:
    eTurn mTurn;
    eGameRule mRule;
    ePlayMode mMode;
    eGameStatus mStatus;
    IAI*                mAI;
    
	int mBoard[15][15];

private:
    std::vector<std::pair<int, int> > mBlackStoneHistory;
    std::vector<std::pair<int, int> > mWhiteStoneHistory;
};