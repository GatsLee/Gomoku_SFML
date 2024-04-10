#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class IScene
{
public:
    IScene();
    virtual ~IScene();

    virtual void init(sf::RenderWindow* window) = 0;
    virtual void update(/* TBD */) = 0;
    virtual void render() = 0;
    virtual void handleInput() = 0;

public:
    enum eSceneType
    {
        START,
        SELECT_MODE,
        GAME,
        GAME_OVER,
    };

private:
    sf::View mView;
    sf::Vector2i mViewGridPosition;
    sf::RenderWindow* mWindow;

    bool mPaused;
    bool mIsRunning;
};