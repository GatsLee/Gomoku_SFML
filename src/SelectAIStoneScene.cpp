#include "AScene.hpp"
#include <SelectAIStoneScene.hpp>

SelectAIStoneScene::SelectAIStoneScene(sf::RenderWindow* window)
    : AScene(SELECT_AI_STONE, window)
{
}

SelectAIStoneScene::~SelectAIStoneScene()
{}

void SelectAIStoneScene::SetStoneText()
{
    int scope[4] = {0, 2, 4, 8};
    int index = static_cast<int>(PlayAIScene::AIRuleSetting);

    sf::Font *font = new sf::Font();
    if (!font->loadFromFile("asset/font/joystix_monospace.otf"))
    {
        std::cerr << "Error: Could not load joystix_monospace.otf" << std::endl;
        exit(1);
    }

    for (int i = scope[index]; i < scope[index + 1]; i++)
    {
        sf::Text *text = new sf::Text(mRuleDescription[i], *font, 15);
        text->setFillColor(sf::Color::Black);
        if (i % 2 == 0 || i == 5) // 0 2 4 5 6
        {
            mBlackStoneText.push_back(text);
        }
        else // 1 3 7
        {
            mWhiteStoneText.push_back(text);
        }
    }

    // Set position
    mBlackStoneText[0]->setPosition(170, 310);
    mWhiteStoneText[0]->setPosition(170, 490);
    if (mBlackStoneText.size() == 3)
    {
        mBlackStoneText[1]->setPosition(165, 328);
        mBlackStoneText[2]->setPosition(170, 346);
    }
}

void SelectAIStoneScene::Init()
{
    
    sf::Texture *textureGoBoard, *textureModalBackground, *textureSelectTitle, \
                *textureBlackStone, *textureWhiteStone;
    textureGoBoard = new sf::Texture();
    textureModalBackground = new sf::Texture();
    textureSelectTitle = new sf::Texture();
    textureBlackStone = new sf::Texture();
    textureWhiteStone = new sf::Texture();
    if (!textureGoBoard->loadFromFile("asset/texture/GoBoard.png") || \
        !textureModalBackground->loadFromFile("asset/texture/ModalBackground3.png") || \
        !textureSelectTitle->loadFromFile("asset/texture/SelectTitle.png") || \
        !textureBlackStone->loadFromFile("asset/texture/BlackStone2.png") || \
        !textureWhiteStone->loadFromFile("asset/texture/WhiteStone2.png"))
    {
        std::cerr << "Error: Could not load go_board.png or modal_background.png or select_title.png" << std::endl;
        exit(1);
    }
    mSprites[GO_BACKGROUND].setTexture(*textureGoBoard);
    mSprites[MODAL_BACKGROUND].setTexture(*textureModalBackground);
    mSprites[SELECT_TITLE].setTexture(*textureSelectTitle);
    mSprites[BLACK_STONE].setTexture(*textureBlackStone);
    mSprites[WHITE_STONE].setTexture(*textureWhiteStone);

    mSprites[GO_BACKGROUND].setScale(0.7407, 0.7407);
    mSprites[GO_BACKGROUND].setColor(sf::Color(255, 255, 255, 100));
    mSprites[BLACK_STONE].setScale(1.2, 1.2);
    mSprites[WHITE_STONE].setScale(1.2, 1.2);

    mSprites[GO_BACKGROUND].setPosition(0, 0);
    mSprites[MODAL_BACKGROUND].setPosition(115, 50);
    mSprites[SELECT_TITLE].setPosition(240, 120);
    mSprites[BLACK_STONE].setPosition(350, 230);
    mSprites[WHITE_STONE].setPosition(350, 410);

    // set stone background
    mRectangles[BLACK_STONE_BACKGROUND] = new sf::RectangleShape();
    mRectangles[BLACK_STONE_BACKGROUND]->setSize(sf::Vector2f(450, 180));
    mRectangles[BLACK_STONE_BACKGROUND]->setFillColor(sf::Color(0, 0, 0, 30));
    mRectangles[BLACK_STONE_BACKGROUND]->setPosition(160, 220);

    mRectangles[WHITE_STONE_BACKGROUND] = new sf::RectangleShape();
    mRectangles[WHITE_STONE_BACKGROUND]->setSize(sf::Vector2f(450, 180));
    mRectangles[WHITE_STONE_BACKGROUND]->setFillColor(sf::Color(0, 0, 0, 30));
    mRectangles[WHITE_STONE_BACKGROUND]->setPosition(160, 400);

    // set Buttons
    mBackButton = new Button(Button::MEDIUM, "Back", sf::Vector2f(300, 600), \
                            sf::Vector2f(60, 22), 26);

    SetStoneText();

    SetIsInit(true);
    SetIsRunning(true);
}

void SelectAIStoneScene::Update(const sf::Vector2i &mousePosition, \
                                std::vector<AScene *> *mScenes, \
                                sf::Event event)
{
    if (IsAnySceneRunning(mScenes) == false)
    {
        SetIsRunning(true);
        if (event.type == sf::Event::MouseButtonReleased)
        {
            AScene::isAnyClickEventHappening = false;
        }
        // update buttons
        mBackButton->update(mousePosition, event);
        // select stone: mouse hover || click event
        if (mRectangles[BLACK_STONE_BACKGROUND]->getGlobalBounds().contains(mousePosition.x, mousePosition.y))
        {
            mRectangles[BLACK_STONE_BACKGROUND]->setFillColor(sf::Color(0, 0, 0, 70));
            if (AScene::isAnyClickEventHappening == false 
                && event.type == sf::Event::MouseButtonPressed \
                && event.mouseButton.button == sf::Mouse::Left)
            {
                PlayAIScene::AITurn = 2;
                SetNextSceneType(AScene::PLAY_AI);
                SetIsRunning(false);
            }
        }
        else
        {
            mRectangles[BLACK_STONE_BACKGROUND]->setFillColor(sf::Color(0, 0, 0, 30));
        }

        if (mRectangles[WHITE_STONE_BACKGROUND]->getGlobalBounds().contains(mousePosition.x, mousePosition.y))
        {
            mRectangles[WHITE_STONE_BACKGROUND]->setFillColor(sf::Color(0, 0, 0, 70));
            if (AScene::isAnyClickEventHappening == false \
                && event.type == sf::Event::MouseButtonPressed \
                && event.mouseButton.button == sf::Mouse::Left)
            {
                PlayAIScene::AITurn = 1;
                SetNextSceneType(AScene::PLAY_AI);
                SetIsRunning(false);
            }
        }
        else
        {
            mRectangles[WHITE_STONE_BACKGROUND]->setFillColor(sf::Color(0, 0, 0, 30));
        }

        // check if buttons are clicked
        if (mBackButton->getState() == Button::ACTIVE)
        {
            SetIsRunning(false);
            mScenes->pop_back();
            mScenes->back()->SetNextSceneType(AScene::NOT_DEFINED);
        }
    }
}

void SelectAIStoneScene::Render()
{
    mWindow->draw(mSprites[GO_BACKGROUND]);
    mWindow->draw(mSprites[MODAL_BACKGROUND]);
    mWindow->draw(mSprites[SELECT_TITLE]);
    mWindow->draw(*mRectangles[BLACK_STONE_BACKGROUND]);
    mWindow->draw(*mRectangles[WHITE_STONE_BACKGROUND]);
    mWindow->draw(mSprites[BLACK_STONE]);
    mWindow->draw(mSprites[WHITE_STONE]);
    for (auto &text : mBlackStoneText)
    {
        mWindow->draw(*text);
    }
    for (auto &text : mWhiteStoneText)
    {
        mWindow->draw(*text);
    }
    mBackButton->render(mWindow);
}