#pragma once

#include "SFML/System/Vector2.hpp"
#include <SFML/Graphics.hpp>
#include <IAI.hpp>
#include <AScene.hpp>
#include <iostream>

class GameHandler
{
public:
    enum eGameUnit
    {
        BLACK_STONE = 1,
        WHITE_STONE = 2,
        BOARD_SIZE = 15,
        MAX_STONE = 225,
    };

    enum eTurn
    {
        BLACK_TURN = 0,
        WHITE_TURN = 1,
    };

    enum eGameStatus
    {
        GAME_READY,
        GAME_RUNNING,
        GAME_PAUSE,
        GAME_WHITE_WIN,
        GAME_BLACK_WIN,
    };

public:
    GameHandler();
    ~GameHandler();

    bool PlaceStone(sf::Vector2i position);



    // void run();
    // void playLocalGame();
    // void playAIGame();
    // void pauseGame();

private:
    eTurn mTurn;
    IAI*                mAI;
    
	int mBoard[15][15] = {0};

private:
    std::vector<std::pair<int, int> > mBlackStoneHistory;
    std::vector<std::pair<int, int> > mWhiteStoneHistory;
};