#pragma once

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <AScene.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>

class Button
{
public:
    enum eButtonState
    {
        IDLE = 0,
        HOVER,
        ACTIVE
    };

    enum eButtonSize
    {
        SMALL = 0,
        MEDIUM,
        LARGE
    };

public:
    Button(std::string fileLocation, sf::Vector2f buttonPosition);
    Button(enum eButtonSize buttonSize, std::string text, \
            sf::Vector2f buttonPosition, sf::Vector2f textPosition, int fontSize = 30);
    ~Button();

    sf::String getText() const;
    sf::Vector2f getPosition() const;
    enum eButtonState getState() const;

    void setText(const sf::String &text);
    void setPosition(const sf::Vector2f &position);
    void setState(enum eButtonState state);
    void setScale(float x, float y);

    void update(const sf::Vector2i &mousePosition, sf::Event event);
    void render(sf::RenderWindow *window);

private:
    eButtonState mButtonState;
    sf::Sprite mOriginal;
    sf::Sprite mHover;
    sf::Sprite *mCurrent;
    sf::Text mText;

    int mFontSize;
};
