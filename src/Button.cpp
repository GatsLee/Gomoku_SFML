#include "SFML/Window/Event.hpp"
#include <Button.hpp>

bool Button::isAnyButtonClicked = false;

Button::Button(std::string fileLocation, sf::Vector2f buttonPosition)
    : mButtonState(IDLE)
{
    // set Button Sprite
    sf::Texture *texture = new sf::Texture();
    sf::Texture *textureHover = new sf::Texture();
    if (!texture->loadFromFile(fileLocation) \
        || !textureHover->loadFromFile(fileLocation))
    {
        std::cerr << "Error: Could not load texture for Button" << std::endl;
        exit(1);
    }

    mOriginal.setTexture(*texture);
    mOriginal.setPosition(buttonPosition);

    mHover.setTexture(*textureHover);
    mHover.setPosition(buttonPosition);
    mHover.setColor(sf::Color(128, 128, 128));

    mCurrent = &mOriginal;
}

Button::Button(enum eButtonSize buttonSize, std::string text, \
                sf::Vector2f buttonPosition, sf::Vector2f textPosition, int fontSize)
    : mButtonState(IDLE)
{
    // set Button Sprite
    sf::Texture *texture = new sf::Texture();
    sf::Texture *textureHover = new sf::Texture();
    if (!texture->loadFromFile("asset/texture/GomokuButton2.png")
        || !textureHover->loadFromFile("asset/texture/GomokuButton2.png"))
    {
        std::cerr << "Error: Could not load GomokuButton.png" << std::endl;
        exit(1);
    }
    
    mOriginal.setTexture(*texture);
    mOriginal.setPosition(buttonPosition);

    mHover.setTexture(*textureHover);
    mHover.setPosition(buttonPosition);
    mHover.setColor(sf::Color(128, 128, 128));

    // set Button Text
    sf::Text textObj;
    sf::Font * font = new sf::Font();
    if (!font->loadFromFile("asset/font/joystix_monospace.otf"))
    {
        std::cerr << "Error: Could not load joystix_monospace.otf" << std::endl;
        exit(1);
    }

    textObj.setString(text);
    // 110, 28 for 4 letters
    textObj.setPosition(buttonPosition.x + textPosition.x, buttonPosition.y + textPosition.y);
    textObj.setFillColor(sf::Color::Black);
    textObj.setFont(*font);
    textObj.setCharacterSize(fontSize);
    mText = textObj;

    mCurrent = &mOriginal;
}

Button::~Button()
{
}

sf::String Button::getText() const
{
    return mText.getString();
}

sf::Vector2f Button::getPosition() const
{
    return mOriginal.getPosition();
}

enum Button::eButtonState Button::getState() const
{
    return mButtonState;
}

void Button::setPosition(const sf::Vector2f &position)
{
    mOriginal.setPosition(position);
    mHover.setPosition(position);
    mText.setPosition(position.x + 5, position.y + 5);
}

void Button::setState(enum eButtonState state)
{
    this->mButtonState = state;
}

void Button::setText(const sf::String &text)
{
    mText.setString(text);
}

void Button::update(const sf::Vector2i &mousePosition, sf::Event event)
{
    this->mButtonState = IDLE;
    if ((*mCurrent).getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)))
    {
        this->mButtonState = HOVER;

        if (event.type == sf::Event::MouseButtonPressed \
            && event.mouseButton.button == sf::Mouse::Left
            && isAnyButtonClicked == false)
        {
            this->mButtonState = ACTIVE;
            isAnyButtonClicked = true;
        }
        else if (event.type == sf::Event::MouseButtonReleased \
                && event.mouseButton.button == sf::Mouse::Left)
        {
            isAnyButtonClicked = false;
        }
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