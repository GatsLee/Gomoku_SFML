#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class AScene
{
public:
    AScene();
    virtual ~AScene();

    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;
    virtual void HandleInput() = 0;

public:
    enum eSceneType
    {
        START_MENU,
        GAME,
        GAME_OVER,
    };

private:
    sf::View mView;
    sf::Vector2i mViewGridPosition;
    sf::RenderWindow* mWindow;
    sf::Font mFont;

    bool mPaused;
    bool mIsRunning;

    sf::Vector2i mMousePosition;
    sf::Vector2i mMouseGridPosition;
    sf::Vector2i mMouseGridPositionOld;
};