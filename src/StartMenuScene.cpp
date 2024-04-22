#include <StartMenuScene.hpp>

StartMenuScene::StartMenuScene(sf::RenderWindow* window)
    : AScene(START_MENU, window)
{
    std::cout << window << std::endl;
}

StartMenuScene::~StartMenuScene()
{}

void StartMenuScene::Init()
{
    // set Sprites
    sf::Texture* textureGoBackground, *textMenuTitle, *textModalBackground;
    textureGoBackground = new sf::Texture();
    textMenuTitle = new sf::Texture();
    textModalBackground = new sf::Texture();
    if (!textureGoBackground->loadFromFile("asset/texture/GoBoard.png")
        || !textMenuTitle->loadFromFile("asset/texture/GomokuTitle.png")
        || !textModalBackground->loadFromFile("asset/texture/ModalBackground3.png"))
    {
        std::cerr << "Error: Could not load texture for Start Menu" << std::endl;
        exit(1);
    }
    mSprites[GO_BACKGROUND].setTexture(*textureGoBackground);
    mSprites[GO_BACKGROUND].setScale(0.7407, 0.7407);
    mSprites[GO_BACKGROUND].setColor(sf::Color(255, 255, 255, 100));
    mSprites[MODAL_BACKGROUND].setTexture(*textModalBackground);
    mSprites[MENU_TITLE].setTexture(*textMenuTitle);
    mSprites[MENU_TITLE].setScale(0.6, 0.6);

    mSprites[GO_BACKGROUND].setPosition(0, 0);
    mSprites[MODAL_BACKGROUND].setPosition(115, 50);
    mSprites[MENU_TITLE].setPosition(180, 120);

    // set Text
    sf::Font * font = new sf::Font();
    if (!font->loadFromFile("asset/font/joystix_monospace.otf"))
    {
        std::cerr << "Error: Could not load joystix_monospace.otf" << std::endl;
        exit(1);
    }
    mMakerText = new sf::Text("Made by Joon-Lee", *font, 20);
    mMakerText->setFillColor(sf::Color::Black);
    mMakerText->setPosition(260, 230);



    // set Buttons
    mPlayButton = new Button("Play", sf::Vector2f(240, 350));
    mExitButton = new Button("Exit", sf::Vector2f(240,460));
}

void StartMenuScene::Update(const sf::Vector2i &mousePosition)
{
    // update buttons
    mPlayButton->update(mousePosition);
    mExitButton->update(mousePosition);

    // check if buttons are clicked
    if (mPlayButton->getState() == Button::ACTIVE)
    {
        mNextSceneType = SELECT_MODE;
    }
    else if (mExitButton->getState() == Button::ACTIVE)
    {
        exit(0);
    }
}

void StartMenuScene::Render()
{
    // draw sprites
    mWindow->draw(mSprites[GO_BACKGROUND]);
    mWindow->draw(mSprites[MODAL_BACKGROUND]);
    mWindow->draw(mSprites[MENU_TITLE]);

    // draw text
    mWindow->draw(*mMakerText);

    // draw buttons
    mPlayButton->render(mWindow);
    mExitButton->render(mWindow);
}