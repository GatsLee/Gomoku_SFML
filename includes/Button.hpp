#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Button
{
public:
    Button(sf::Texture *original, sf::Texture *hover, std::string text, sf::Vector2f position);
    ~Button();

    sf::String getText() const;
    bool isHover() const;
    
    void setHover(bool hover);
    void setText(const sf::String &text);

private:
    sf::Sprite mOriginal;
    sf::Sprite mHover;
    sf::Sprite *mCurrent;
    sf::Text mText;
    bool mIsHover;
};
