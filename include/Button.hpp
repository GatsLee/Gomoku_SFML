#pragma once

#include "SFML/Window/Event.hpp"
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <thread>

class Button
{
public:
    enum eButtonState
    {
        IDLE = 0,
        HOVER,
        ACTIVE
    };

public:
    Button(std::string text, \
            sf::Vector2f buttonPosition, sf::Vector2f textPosition);
    ~Button();

    sf::String getText() const;
    sf::Vector2f getPosition() const;
    enum eButtonState getState() const;

    void setText(const sf::String &text);
    void setPosition(const sf::Vector2f &position);
    void setState(enum eButtonState state);

    void update(const sf::Vector2i &mousePosition, sf::Event event);
    void render(sf::RenderWindow *window);

private:
    eButtonState mButtonState;
    sf::Sprite mOriginal;
    sf::Sprite mHover;
    sf::Sprite *mCurrent;
    sf::Text mText;
};
