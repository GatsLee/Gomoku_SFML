#include "SFML/Graphics/Font.hpp"
#include <GameOverScene.hpp>

GameOverScene::GameOverScene(sf::RenderWindow* window)
    : AScene(GAME_OVER, window)
{
    mWinner = PlayLocalScene::WinnerName;
}

GameOverScene::~GameOverScene()
{}

void GameOverScene::Init()
{
    //set Sprites
    sf::Texture* textureGoBackground, *textGameOverTitle, *textModalBackground;
    textureGoBackground = new sf::Texture();
    textGameOverTitle = new sf::Texture();
    textModalBackground = new sf::Texture();
    if (!textureGoBackground->loadFromFile("asset/texture/GoBoard.png")
        || !textGameOverTitle->loadFromFile("asset/texture/GameOverTitle.png")
        || !textModalBackground->loadFromFile("asset/texture/ModalBackground3.png"))
    {
        std::cerr << "Error: Could not load texture for Game Over Menu" << std::endl;
        exit(1);
    }
    mSprites[GO_BACKGROUND].setTexture(*textureGoBackground);
    mSprites[GO_BACKGROUND].setScale(0.7407, 0.7407);
    mSprites[GO_BACKGROUND].setColor(sf::Color(255, 255, 255, 100));
    mSprites[MODAL_BACKGROUND].setTexture(*textModalBackground);
    mSprites[GAMEOVER_TITLE].setTexture(*textGameOverTitle);

    mSprites[GO_BACKGROUND].setPosition(0, 0);
    mSprites[MODAL_BACKGROUND].setPosition(115, 50);
    mSprites[GAMEOVER_TITLE].setPosition(150, 120);
    
    //set Text
    sf::Font* font = new sf::Font();
    if (!font->loadFromFile("asset/font/joystix_monospace.otf"))
    {
        std::cerr << "Error: Could not load font for Game Over Menu" << std::endl;
        exit(1);
    }
    mWinnerText = new sf::Text();
    mWinnerText->setFont(*font);
    mWinnerText->setString(mWinner + " Wins!");
    mWinnerText->setFillColor(sf::Color::Black);

    mWinnerText->setPosition(250, 200);

    //set Buttons
    mPlayAgainButton = new Button(Button::LARGE, "Play Again", sf::Vector2f(230, 300), sf::Vector2f(50, 26), 26);
    mBackToSelectModeButton = new Button(Button::LARGE, "Select Mode", sf::Vector2f(230, 410), sf::Vector2f(40, 26), 26);
    mQuitButton = new Button(Button::LARGE, "Quit", sf::Vector2f(230, 520), sf::Vector2f(110, 24), 26);

    SetIsInit(true);
    SetIsRunning(true);
}

void GameOverScene::Update(const sf::Vector2i& mousePosition, std::vector<AScene*>* mScenes, sf::Event event)
{
    if (IsAnySceneRunning(mScenes) == false)
    {
        SetIsRunning(true);
        //update buttons
        mPlayAgainButton->update(mousePosition, event);
        mBackToSelectModeButton->update(mousePosition, event);
        mQuitButton->update(mousePosition, event);

        //check if buttons are clicked
        if (mPlayAgainButton->getState() == Button::ACTIVE)
        {
            // SetNextSceneType(AScene::PLAY_LOCAL);
            SetIsRunning(false);
        }
        else if (mBackToSelectModeButton->getState() == Button::ACTIVE)
        {
            // SetNextSceneType(AScene::SELECT_MODE);
            SetIsRunning(false);
        }
        else if (mQuitButton->getState() == Button::ACTIVE)
        {
            SetNextSceneType(AScene::EXIT);
            SetIsRunning(false);
        }
    }
}

void GameOverScene::Render()
{
    mWindow->draw(mSprites[GO_BACKGROUND]);
    mWindow->draw(mSprites[MODAL_BACKGROUND]);
    mWindow->draw(mSprites[GAMEOVER_TITLE]);
    mWindow->draw(*mWinnerText);
    mPlayAgainButton->render(mWindow);
    mBackToSelectModeButton->render(mWindow);
    mQuitButton->render(mWindow);
}