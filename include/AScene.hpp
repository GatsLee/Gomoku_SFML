#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class AScene
{
public:
    enum eSceneType
    {
        START_MENU,
        SELECT_MODE,
        SELECT_LOCAL,
        SELECT_AI,
        PAUSE,
        GAME,
        GAME_OVER,
        NOT_DEFINED
    };

public:
    AScene(eSceneType sceneType, sf::RenderWindow* window);
    virtual ~AScene();

    virtual void Init() = 0;
    virtual void Update(const sf::Vector2i &mousePosition) = 0;
    virtual void Render() = 0;

protected:
    eSceneType mSceneType;
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