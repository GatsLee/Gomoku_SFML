#include "PlayLocalScene.hpp"
#include <SelectLocalRuleScene.hpp>

SelectLocalRuleScene::SelectLocalRuleScene(sf::RenderWindow* window)
    : AScene(SELECT_LOCAL_RULE, window)
{}

SelectLocalRuleScene::~SelectLocalRuleScene()
{}

void SelectLocalRuleScene::Init()
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
    mFreeRuleButton = new Button(Button::LARGE, "Free Rule", sf::Vector2f(240, 250), sf::Vector2f(60, 26), 26);
    mStandardRuleButton = new Button(Button::LARGE,"Standard Rule", sf::Vector2f(240, 360), sf::Vector2f(15, 26), 26);
    mRenjuRuleButton = new Button(Button::LARGE,"Renju Rule", sf::Vector2f(240, 470), sf::Vector2f(50, 26), 26);
    mBackButton = new Button(Button::LARGE, "Back", sf::Vector2f(240, 580), sf::Vector2f(110, 24));
    SetIsInit(true);
    SetIsRunning(true);
}

void SelectLocalRuleScene::Update(const sf::Vector2i& mousePosition, std::vector<AScene*>* mScenes, sf::Event event)
{
    if (IsAnySceneRunning(mScenes) == false)
    {
        SetIsRunning(true);
        // update buttons
        mFreeRuleButton->update(mousePosition, event);
        mStandardRuleButton->update(mousePosition, event);
        mRenjuRuleButton->update(mousePosition, event);
        mBackButton->update(mousePosition, event);

        // check if buttons are clicked
        if (mFreeRuleButton->getState() == Button::ACTIVE)
        {
            SetNextSceneType(AScene::PLAY_LOCAL);
            PlayLocalScene::LocalRuleSetting = 0;
            SetIsRunning(false);
        }
        else if (mStandardRuleButton->getState() == Button::ACTIVE)
        {
            SetNextSceneType(AScene::PLAY_LOCAL);
            PlayLocalScene::LocalRuleSetting = 1;
            SetIsRunning(false);
        }
        else if (mRenjuRuleButton->getState() == Button::ACTIVE)
        {
            SetNextSceneType(AScene::PLAY_LOCAL);
            PlayLocalScene::LocalRuleSetting = 2;
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

void SelectLocalRuleScene::Render()
{
    mWindow->draw(mSprites[GO_BACKGROUND]);
    mWindow->draw(mSprites[MODAL_BACKGROUND]);
    mWindow->draw(mSprites[SELECT_TITLE]);
    mFreeRuleButton->render(mWindow);
    mStandardRuleButton->render(mWindow);
    mRenjuRuleButton->render(mWindow);
    mBackButton->render(mWindow);
}