#include "GameHandler.hpp"
#include "SFML/Graphics/Text.hpp"
#include <PlayLocalScene.hpp>

/**
 * @brief Global Variable for rule setting(0:free, 1:standard, 2:renju)
 */
int PlayLocalScene::LocalRuleSetting = 0;

PlayLocalScene::PlayLocalScene(sf::RenderWindow *window)
    : AScene(PLAY_LOCAL, window)
{}

PlayLocalScene::~PlayLocalScene()
{}

void PlayLocalScene::Init()
{
    // GameHandler init
    mGameHandler = new GameHandler( static_cast<enum GameHandler::eGameRule>(LocalRuleSetting), \
                                     GameHandler::MODE_LOCAL , \
                                     GameHandler::AI_NOTDEFINED);
    // set Sprites
    sf::Texture* textureGoBoard, *textureWhiteGui, *textureBlackGui;
    textureGoBoard = new sf::Texture();
    textureWhiteGui = new sf::Texture();
    textureBlackGui = new sf::Texture();
    if (!textureGoBoard->loadFromFile("asset/texture/GoBoard.png") \
        || !textureWhiteGui->loadFromFile("asset/texture/WhiteStoneGui.png") \
        || !textureBlackGui->loadFromFile("asset/texture/BlackStoneGui.png"))
    {
        std::cerr << "Error: Could not load texture for Play Local Scene" << std::endl;
        exit(1);
    }
    mSprites[GO_BOARD].setTexture(*textureGoBoard);
    mSprites[WHITE_STONE_GUI].setTexture(*textureWhiteGui);
    mSprites[BLACK_STONE_GUI].setTexture(*textureBlackGui);

    mSprites[GO_BOARD].setScale(0.6, 0.6);
    
    mSprites[GO_BOARD].setPosition(300, 300);
    mSprites[WHITE_STONE_GUI].setPosition(0, 0);
    mSprites[BLACK_STONE_GUI].setPosition(550, 0);

    // set Buttons
    mOptionButton = new Button(Button::MEDIUM, "Option", sf::Vector2f(300, 100), sf::Vector2f(50, 24));
    mRuleButton = new Button(Button::MEDIUM, "Rule", sf::Vector2f(300, 150), sf::Vector2f(50, 24));

    SetIsInit(true);
    SetIsRunning(true);
}

void PlayLocalScene::Update(const sf::Vector2i &mousePosition, \
                            std::vector<AScene *> *mScenes, \
                            sf::Event event)
{
    if (IsAnySceneRunning(mScenes) == false)
    {
        SetIsRunning(true);

        // update buttons  
        mOptionButton->update(mousePosition, event);
        mRuleButton->update(mousePosition, event);
        
        // check button clicked
        if (mOptionButton->getState() == Button::ACTIVE)
        {
            SetNextSceneType(AScene::OPTION_POPUP);
            SetIsRunning(false);
        }
        else if (mRuleButton->getState() == Button::ACTIVE)
        {
            SetNextSceneType(AScene::RULE_POPUP);
            SetIsRunning(false);
        }

        // set stone

        // check game status

    }
}

void PlayLocalScene::Render()
{
    // Render
}