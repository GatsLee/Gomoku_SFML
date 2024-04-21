#include <StartMenuScene.hpp>

StartMenuScene::StartMenuScene(sf::RenderWindow* window, AScene::eSceneType &mCurrentSceneType)
    : AScene(START_MENU, window), mCurrentSceneType(mCurrentSceneType)
{}

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
        || !textModalBackground->loadFromFile("asset/texture/ModalBackground.png"))
    {
        std::cerr << "Error: Could not load texture for Start Menu" << std::endl;
        exit(1);
    }
    mSprites[GO_BACKGROUND].setTexture(*textureGoBackground);
    mSprites[GO_BACKGROUND].setScale(0.74, 0.74);
    mSprites[MODAL_BACKGROUND].setTexture(*textModalBackground);
    mSprites[MODAL_BACKGROUND].setScale(0.8, 0.8);
    mSprites[MENU_TITLE].setTexture(*textMenuTitle);
    mSprites[MENU_TITLE].setScale(0.5, 0.5);

    mSprites[GO_BACKGROUND].setPosition(0, 0);
    mSprites[MODAL_BACKGROUND].setPosition(54, 100);
    mSprites[MENU_TITLE].setPosition(210, 130);

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
    mPlayButton = new Button("Play", sf::Vector2f(315, 300));
    mExitButton = new Button("Exit", sf::Vector2f(315, 450));
}

void StartMenuScene::Update(const sf::Vector2i &mousePosition)
{
    // update buttons
    mPlayButton->update(mousePosition);
    mExitButton->update(mousePosition);

    // check if buttons are clicked
    if (mPlayButton->getState() == Button::ACTIVE)
    {
        mCurrentSceneType = SELECT_MODE;
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