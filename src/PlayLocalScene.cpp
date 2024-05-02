#include "GameHandler.hpp"
#include "SFML/Graphics/Sprite.hpp"
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
    
    mSprites[GO_BOARD].setPosition(80, 140);
    mSprites[WHITE_STONE_GUI].setPosition(30, 15);
    mSprites[BLACK_STONE_GUI].setPosition(530, 15);

    // set stone gui
    mSprites[WHITE_STONE_GUI].setScale(0.8, 0.8);
    mSprites[BLACK_STONE_GUI].setScale(0.8, 0.8);

    // set font
    sf::Font *font = new sf::Font();
    if (!font->loadFromFile("asset/font/joystix_monospace.otf"))
    {
        std::cerr << "Error: Could not load joystix_monospace.otf" << std::endl;
        exit(1);
    }
    mPlayerOneName  = new sf::Text("Player 1", *font, 25);
    mPlayerTwoName  = new sf::Text("Player 2", *font, 25);

    mPlayerOneName->setFillColor(sf::Color::Black);
    mPlayerTwoName->setFillColor(sf::Color::Black);
    mPlayerOneName->setPosition(mSprites[WHITE_STONE_GUI].getGlobalBounds().getPosition().x + 63, \
                                 mSprites[WHITE_STONE_GUI].getGlobalBounds().getPosition().y + 10);
    mPlayerTwoName->setPosition(mSprites[BLACK_STONE_GUI].getGlobalBounds().getPosition().x + 63, \
                                    mSprites[BLACK_STONE_GUI].getGlobalBounds().getPosition().y + 10);

    // set background
    mWhiteBackground.setSize(sf::Vector2f(800, 800));
    mWhiteBackground.setFillColor(sf::Color::White);

    // set Buttons
    mOptionButton = new Button(Button::MEDIUM, "Option", sf::Vector2f(320, 10), sf::Vector2f(22, 13), 25);
    mRuleButton = new Button(Button::MEDIUM, "Rule", sf::Vector2f(320, 75), sf::Vector2f(40, 13), 25);

    mOptionButton->setScale(0.8, 0.8);
    mRuleButton->setScale(0.8, 0.8);

    SetIsInit(true);
    SetIsRunning(true);

    //test for draw stone
    sf::Texture *textureBlackStone = new sf::Texture();
    if (!textureBlackStone->loadFromFile("asset/texture/BlackStone2.png"))
    {
        std::cerr << "Error: Could not load BlackStone.png" << std::endl;
        exit(1);
    }
    // textureBlackStone->setSmooth(true);
    spriteBlackStone = new sf::Sprite();
    spriteBlackStone->setTexture(*textureBlackStone);
    // spriteBlackStone->setScale(0.8, 0.8);
    spriteBlackStone->setPosition(300, 300);

}

void PlayLocalScene::Update(const sf::Vector2i &mousePosition, \
                            std::vector<AScene *> *mScenes, \
                            sf::Event event)
{
    if (IsAnySceneRunning(mScenes) == false)
    {
        SetIsRunning(true);
        // check keyboard input
        if (event.type == sf::Event::KeyPressed
            && event.key.code == sf::Keyboard::Escape)
        {
            SetNextSceneType(AScene::OPTION_POPUP);
            SetIsRunning(false);
        }
    
        // 102 160: start of go board
        std::cout << mousePosition.x << " " << mousePosition.y << std::endl;
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

    // draw background
    mWindow->draw(mWhiteBackground);
    // draw go board
    mWindow->draw(mSprites[GO_BOARD]);
    // draw stone gui
    mWindow->draw(mSprites[WHITE_STONE_GUI]);
    mWindow->draw(mSprites[BLACK_STONE_GUI]);
    // draw player name
    mWindow->draw(*mPlayerOneName);
    mWindow->draw(*mPlayerTwoName);
    // draw buttons
    mOptionButton->render(mWindow);
    mRuleButton->render(mWindow);
}