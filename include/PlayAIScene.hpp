#pragma once

#include "SFML/Graphics/CircleShape.hpp"
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <AScene.hpp>
#include <Button.hpp>
#include <GameHandler.hpp>
#include <vector>
#include <cmath>

class PlayAIScene : public AScene
{
public:
    enum ePlayAISceneUnit
    {
        GO_BOARD_X = 101,
        GO_BOARD_Y = 160,
        GO_BOARD_GAP = 43,
        GO_BOARD_PADDING = 15,
        STONE_RADIUS = 56,
    };

    enum eTmpStoneType
    {
        AVAILABLE,
        THREE_THREE_BAN,
        FOUR_FOUR_BAN,
    };

    enum eAIStatus
    {
        CALCULATE_MOVE,
        SHOW_INFO,
        PLACE_STONE,
        // 
        PLAYER_TURN,
    };

public:
    PlayAIScene(sf::RenderWindow* window);
    ~PlayAIScene();

    void Init();
    void Update(const sf::Vector2i &mousePosition, \
                std::vector<AScene *> *mScenes, \
                sf::Event event);
    void Render();

    void UpdateAIStone();
    void UpdatePlayerStone(const sf::Vector2i &mousePosition);
    void DrawStone();

    void ResetGameHandler();

    static int AIRuleSetting;
    static int AITurn;

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

    GameHandler* mGameHandler;

    sf::Sprite mSprites[3];
    sf::RectangleShape mWhiteBackground;

    sf::Text *mPlayerOneName;
    sf::Text *mPlayerTwoName;

    sf::Sprite *spriteBlackStone;
    sf::Sprite *spriteWhiteStone;
    sf::CircleShape *mPossibleStone;
    sf::Text        *mTimeText;

    sf::Sprite mTmpStoneSprites[2];
    sf::Sprite *mCurrentTmpStoneSprite;

    std::pair<int, int> mStoneTmpPosition;

    eAIStatus mAIStatus;
    double mTimeElapsed;
};