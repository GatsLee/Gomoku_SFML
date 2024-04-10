#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <bitset>

class GameHandler
{
public:
    GameHandler();
    ~GameHandler();

    void run();

private:
    enum GameState
    {
        START_MENU,
        SELECT_MODE,
        PLAYING,
        PAUSE,
        END_GAME,
    };
    std::bitset<5> mGameState;
    

};