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

    eSceneType GetSceneType() { return mSceneType; }
    eSceneType GetNextSceneType() { return mNextSceneType; }

    void SetNextSceneType(eSceneType nextSceneType) { mNextSceneType = nextSceneType; }
protected:
    eSceneType mSceneType;
    eSceneType mNextSceneType;
    sf::View mView;
    sf::Vector2i mViewGridPosition;
    sf::RenderWindow* mWindow;
    sf::Font mFont;
};