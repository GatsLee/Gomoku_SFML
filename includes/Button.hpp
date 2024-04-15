#pragma once

#include "SFML/Graphics/Color.hpp"
#include "SFML/System/Vector2.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

class Button
{
public:
    Button(sf::Texture *original, sf::Texture *hover, \
            std::string text, sf::Vector2f position, \
            float width, float height);
    ~Button();

    sf::String getText() const;
    void setText(const sf::String &text);

    void update(const sf::Vector2i &mousePosition);
    void render(sf::RenderWindow *window);

public:
    enum eButtonState
    {
        IDLE = 0,
        HOVER,
        ACTIVE
    };

private:
    eButtonState mButtonState;
    sf::Sprite mOriginal;
    sf::Sprite mHover;
    sf::Sprite *mCurrent;
    sf::Text mText;
};
