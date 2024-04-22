#include <Button.hpp>

Button::Button(std::string text, sf::Vector2f position)
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
    mOriginal.setPosition(position);

    mHover.setTexture(*textureHover);
    mHover.setPosition(position);
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
    textObj.setPosition(position.x + 110, position.y + 28);
    textObj.setFillColor(sf::Color::Black);
    textObj.setFont(*font);
    textObj.setCharacterSize(30);
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

void Button::update(const sf::Vector2i &mousePosition)
{
    this->mButtonState = IDLE;

    if ((*mCurrent).getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)))
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