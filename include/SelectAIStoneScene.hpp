#pragma once

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <PlayAIScene.hpp>
#include <AScene.hpp>
#include <Button.hpp>

class SelectAIStoneScene final: public AScene
{
public:
    enum eTextureType
    {
        GO_BACKGROUND,
        MODAL_BACKGROUND,
        SELECT_TITLE,
        BLACK_STONE,
        WHITE_STONE,
    };

    enum eStoneBackgroundType
    {
        BLACK_STONE_BACKGROUND,
        WHITE_STONE_BACKGROUND,
    };

    enum eRuleDescriptionType
    {
        FREE_BLACK,
        FREE_WHITE,
        STANDARD_BLACK,
        STANDARD_WHITE,
        RENJU_BLACK_FIRST,
        RENJU_BLACK_SECOND,
        RENJU_WHITE,
    };

public:
    SelectAIStoneScene(sf::RenderWindow* window);
    ~SelectAIStoneScene();

    void Init();
    void Update(const sf::Vector2i &mousePosition, \
                std::vector<AScene *> *mScenes, \
                sf::Event event);
    void Render();


private:
    void SetStoneText();

private:
    std::string mRuleDescription[8] = {"More than 5 stones in a row can win", \
                                        "More than 5 stones in a row can win", \
                                        "No 3_3, 5 stones in a row can win", \
                                        "No 3_3, 5 stones in a row can win", \
                                        "No 3(4)_3(4), 5 stones in a row can win", \
                                        "(Though last move is not allowed,", \
                                        "you can place the stone)", \
                                        "No limit, 5 stones in a row can win"};

    sf::Sprite mSprites[5];
    sf::RectangleShape *mRectangles[2];
    Button *mBackButton;

    std::vector<sf::Text *>mBlackStoneText;
    std::vector<sf::Text *>mWhiteStoneText;

};