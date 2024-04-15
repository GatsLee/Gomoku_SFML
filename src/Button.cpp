#include <Button.hpp>

Button::Button(sf::Texture *original, sf::Texture *hover, \
            std::string text, sf::Vector2f position, \
            float width, float height)
    : mButtonState(IDLE)
    , mOriginal(*original)
    , mHover(*hover)
{
    mOriginal.setPosition(position);
    mHover.setPosition(position);
    mText.setString(text);
    mText.setPosition(position.x + 10, position.y + 10);
    mCurrent = &mOriginal;
    mText.setFillColor(sf::Color::Black);

    std::cout << "Button created" << std::endl;
}

Button::~Button()
{
    std::cout << "Button destroyed" << std::endl;
}

sf::String Button::getText() const
{
    return mText.getString();
}

void Button::setText(const sf::String &text)
{
    mText.setString(text);
}

void Button::update(const sf::Vector2i &mousePosition)
{
    this->mButtonState = IDLE;

    if (mCurrent->getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)))
    {
        this->mButtonState = HOVER;

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            this->mButtonState = ACTIVE;
    }

    switch (this->mButtonState)
    {
    case IDLE:
        this->mCurrent = &mOriginal;
        break;
    case HOVER:
        this->mCurrent = &mHover;
        break;
    case ACTIVE:
        this->mCurrent = &mHover;
        break;
    };
}

void Button::render(sf::RenderWindow *window)
{
    window->draw(*mCurrent);
    window->draw(mText);
}