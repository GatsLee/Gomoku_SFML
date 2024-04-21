#pragma once

#include <SFML/Graphics.hpp>
#include <IAI.hpp>
#include <AScene.hpp>
#include <iostream>

class GameHandler
{
public:
    GameHandler();
    ~GameHandler();

    void run();
    void playLocalGame();
    void playAIGame();
    void pauseGame();
public:
    enum eGameUnit
    {
        BLACK_STONE = 1,
        WHITE_STONE = 2,
        BOARD_SIZE = 15,
    };

private:
    IAI*                mAI;
    
	int mBoard[15][15] = {0};
};