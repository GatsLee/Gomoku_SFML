#include <Button.hpp>

Button::Button(sf::Texture *original, sf::Texture *hover, std::string text, sf::Vector2f position)
{

    mOriginal.setTexture(*original);
    mHover.setTexture(*hover);
    mOriginal.setPosition(position);
    mHover.setPosition(position);
    mText.setString(text);
    mText.setPosition(position.x + 10, position.y + 10);
    mIsHover = false;
    mCurrent = &mOriginal;
}

Button::~Button()
{
    std::cout << "Button destroyed" << std::endl;
}

sf::String Button::getText() const
{
    return mText.getString();
}

bool Button::isHover() const
{
    return mIsHover;
}

void Button::setHover(bool hover)
{
    mIsHover = hover;
    mCurrent = hover ? &mHover : &mOriginal;
}

void Button::setText(const sf::String &text)
{
    mText.setString(text);
}
