#pragma once

#include "SFML/Graphics/RectangleShape.hpp"
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <AScene.hpp>
#include <Button.hpp>
#include <GameHandler.hpp>
#include <vector>
#include <cmath>
#include <iostream>

class PlayLocalScene : public AScene
{
public:
    enum ePlayLocalSceneUnit
    {
        GO_BOARD_X = 101,
        GO_BOARD_Y = 160,
        GO_BOARD_GAP = 43,
        GO_BOARD_PADDING = 15,
        STONE_RADIUS = 56,
    };

public:
    PlayLocalScene(sf::RenderWindow* window);
    ~PlayLocalScene();

    void Init();
    void Update(const sf::Vector2i &mousePosition, \
                std::vector<AScene *> *mScenes, \
                sf::Event event);
    void Render();

    void UpdateStone(const sf::Vector2i &mousePosition);
    void DrawStone();

    static int LocalRuleSetting;
private:
    enum eTextureType
    {
        BLACK_STONE_GUI,
        WHITE_STONE_GUI,
        GO_BOARD,
    };
    
    GameHandler *mGameHandler;

    sf::Sprite mSprites[3];
    sf::RectangleShape mWhiteBackground;
    Button *mOptionButton;
    Button *mRuleButton;

    sf::Text *mPlayerOneName;
    sf::Text *mPlayerTwoName;

    sf::Sprite *spriteBlackStone;
    sf::Sprite *spriteWhiteStone;

    std::pair<int, int> mStoneTmpPosition;
};