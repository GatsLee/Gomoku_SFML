#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Scene
{
public:


private:
    sf::View mView;
    sf::Vector2i mViewGridPosition;
    sf::RenderWindow* mWindow;

    bool mPaused;
    bool mIsRunning;

    
};