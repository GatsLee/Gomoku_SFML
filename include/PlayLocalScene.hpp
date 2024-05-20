#pragma once

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <AScene.hpp>
#include <Button.hpp>
#include <GameHandler.hpp>
#include <vector>
#include <cmath>

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
    enum eTmpStoneType
    {
        AVAILABLE,
        THREE_THREE_BAN,
        FOUR_FOUR_BAN,
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

    static std::string WinnerName;
private:
    enum eTextureType
    {
        BLACK_STONE_GUI,
        WHITE_STONE_GUI,
        GO_BOARD,
    };

    enum eTmpTextureType
    {
        THREE_THREE_BAN_GUI,
        FOUR_FOUR_BAN_GUI,
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

    sf::Sprite mTmpStoneSprites[2];
    sf::Sprite *mCurrentTmpStoneSprite;

    // for temporary stone: available, 3-3 ban, 4-4 ban
    std::pair<int, int> mStoneTmpPosition;
};