#include <SelectModeScene.hpp>

SelectModeScene::SelectModeScene(sf::RenderWindow* window)
    : AScene(SELECT_MODE, window)
{
    std::cout << window << std::endl;
}

SelectModeScene::~SelectModeScene()
{
}

void SelectModeScene::Init()
{
    // set Sprites
    sf::Texture* textureGoBackground, *textSelectTitle, *textModalBackground;
    textureGoBackground = new sf::Texture();
    textSelectTitle = new sf::Texture();
    textModalBackground = new sf::Texture();
    if (!textureGoBackground->loadFromFile("asset/texture/GoBoard.png")
        || !textSelectTitle->loadFromFile("asset/texture/SelectTitle.png")
        || !textModalBackground->loadFromFile("asset/texture/ModalBackground3.png"))
    {
        std::cerr << "Error: Could not load texture for Select Menu" << std::endl;
        exit(1);
    }
    mSprites[GO_BACKGROUND].setTexture(*textureGoBackground);
    mSprites[GO_BACKGROUND].setScale(0.7407, 0.7407);
    mSprites[GO_BACKGROUND].setColor(sf::Color(255, 255, 255, 100));
    mSprites[MODAL_BACKGROUND].setTexture(*textModalBackground);
    mSprites[SELECT_TITLE].setTexture(*textSelectTitle);
    mSprites[SELECT_TITLE].setScale(0.5, 0.5);

    mSprites[GO_BACKGROUND].setPosition(0, 0);
    mSprites[MODAL_BACKGROUND].setPosition(115, 50);
    mSprites[SELECT_TITLE].setPosition(180, 120);

    // set Buttons
    mPlayLocalButton = new Button("Play Local", sf::Vector2f(315, 350));
    mPlayAIButton = new Button("Play AI", sf::Vector2f(315, 460));
    mBackButton = new Button("Back", sf::Vector2f(315, 570));
}

void SelectModeScene::Update(const sf::Vector2i &mousePosition)
{
    // update buttons
    mPlayLocalButton->update(mousePosition);
    mPlayAIButton->update(mousePosition);
    mBackButton->update(mousePosition);

    // check if buttons are clicked
    if (mPlayLocalButton->getState() == Button::ACTIVE)
    {
        SetNextSceneType(AScene::SELECT_LOCAL);
    }
    else if (mPlayAIButton->getState() == Button::ACTIVE)
    {
        SetNextSceneType(AScene::SELECT_AI);
    }
    else if (mBackButton->getState() == Button::ACTIVE)
    {
        SetNextSceneType(AScene::START_MENU);
    }
}

void SelectModeScene::Render()
{
    mWindow->draw(mSprites[GO_BACKGROUND]);
    mWindow->draw(mSprites[MODAL_BACKGROUND]);
    mWindow->draw(mSprites[SELECT_TITLE]);
    mPlayLocalButton->render(mWindow);
    mPlayAIButton->render(mWindow);
    mBackButton->render(mWindow);
}