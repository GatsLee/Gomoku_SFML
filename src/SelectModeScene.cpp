#include <SelectModeScene.hpp>

SelectModeScene::SelectModeScene(sf::RenderWindow* window)
    : AScene(SELECT_MODE, window)
{}

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

    mSprites[GO_BACKGROUND].setPosition(0, 0);
    mSprites[MODAL_BACKGROUND].setPosition(115, 50);
    mSprites[SELECT_TITLE].setPosition(240, 120);

    // set Buttons
    mPlayLocalButton = new Button("Play Local", sf::Vector2f(240, 250), sf::Vector2f(35, 24));
    mPlayAIButton = new Button("Play AI", sf::Vector2f(240, 360), sf::Vector2f(70, 24));
    mBackButton = new Button("Back", sf::Vector2f(240, 470), sf::Vector2f(110, 24));
    SetIsInit(true);
    SetIsRunning(true);
}

void SelectModeScene::Update(const sf::Vector2i& mousePosition, std::vector<AScene*>* mScenes, sf::Event event)
{
    if (IsAnySceneRunning(mScenes) == false)
    {
        SetIsRunning(true);
        // update buttons
        mPlayLocalButton->update(mousePosition, event);
        mPlayAIButton->update(mousePosition, event);
        mBackButton->update(mousePosition, event);

        // check if buttons are clicked
        if (mPlayLocalButton->getState() == Button::ACTIVE)
        {
            SetNextSceneType(AScene::PLAY_LOCAL);
            SetIsRunning(false);
        }
        else if (mPlayAIButton->getState() == Button::ACTIVE)
        {
            SetNextSceneType(AScene::SELECT_AI);
            SetIsRunning(false);
        }
        else if (mBackButton->getState() == Button::ACTIVE)
        {
            SetIsRunning(false);
            mScenes->pop_back();
            mScenes->back()->SetNextSceneType(AScene::NOT_DEFINED);
        }
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