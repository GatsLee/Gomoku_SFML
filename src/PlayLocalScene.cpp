#include <PlayLocalScene.hpp>

/**
 * @brief Global Variable for rule setting(0:free, 1:standard, 2:renju)
 */
int PlayLocalScene::LocalRuleSetting = 0;


/**
 * @brief Global Variable for winner name
 */
std::string PlayLocalScene::WinnerName = "";

PlayLocalScene::PlayLocalScene(sf::RenderWindow *window)
    : AScene(PLAY_LOCAL, window)
{}

PlayLocalScene::~PlayLocalScene()
{}

void PlayLocalScene::Init()
{
    // GameHandler init
    mGameHandler = new GameHandler( static_cast<enum GameHandler::eGameRule>(LocalRuleSetting), \
                                     GameHandler::MODE_LOCAL);
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

    // set stone sprite
    sf::Texture *textureBlackStone = new sf::Texture();
    sf::Texture *textureWhiteStone = new sf::Texture();
    if (!textureBlackStone->loadFromFile("asset/texture/BlackStone2.png")
        || !textureWhiteStone->loadFromFile("asset/texture/WhiteStone2.png"))
    {
        std::cerr << "Error: Could not load BlackStone.png" << std::endl;
        exit(1);
    }
    spriteBlackStone = new sf::Sprite();
    spriteWhiteStone = new sf::Sprite();
    spriteBlackStone->setTexture(*textureBlackStone);
    spriteWhiteStone->setTexture(*textureWhiteStone);
    spriteBlackStone->setScale(0.6, 0.6);
    spriteWhiteStone->setScale(0.6, 0.6);

    // set temporary stone sprite
    sf::Texture *textureThreeThreeBan, *textureFourFourBan;
    textureThreeThreeBan = new sf::Texture();
    textureFourFourBan = new sf::Texture();
    if (!textureThreeThreeBan->loadFromFile("asset/texture/ThreeThreeBan.png") \
        || !textureFourFourBan->loadFromFile("asset/texture/FourFourBan.png"))
    {
        std::cerr << "Error: Could not load ThreeThreeBan.png or FourFourBan.png" << std::endl;
        exit(1);
    }
    mTmpStoneSprites[THREE_THREE_BAN_GUI].setTexture(*textureThreeThreeBan);
    mTmpStoneSprites[FOUR_FOUR_BAN_GUI].setTexture(*textureFourFourBan);
    mTmpStoneSprites[THREE_THREE_BAN_GUI].setScale(0.6, 0.6);
    mTmpStoneSprites[FOUR_FOUR_BAN_GUI].setScale(0.6, 0.6);

    mStoneTmpPosition = std::make_pair(-1, -1);
    mCurrentTmpStoneSprite = nullptr;

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
        if (event.type == sf::Event::MouseButtonReleased)
        {
            AScene::isAnyClickEventHappening = false;
        }
        // check keyboard input
        if (event.type == sf::Event::KeyPressed
            && event.key.code == sf::Keyboard::Escape)
        {
            SetNextSceneType(AScene::OPTION_POPUP);
            SetIsRunning(false);
        }

        // set stone
        UpdateStone(mousePosition);

        // check game status
        if (mGameHandler->GetGameStatus() != GameHandler::GAME_ONGOING)
        {
            if (mGameHandler->GetGameStatus() == GameHandler::GAME_BLACK_WIN)
            {
                WinnerName = "Player 1";
            }
            else if (mGameHandler->GetGameStatus() == GameHandler::GAME_WHITE_WIN)
            {
                WinnerName = "Player 2";
            }
            SetNextSceneType(AScene::GAME_OVER);
            SetIsRunning(false);
        }
    }
}

void PlayLocalScene::UpdateStone(const sf::Vector2i &mousePosition)
{
    int x = -1, y = -1;

    // Check if the mousePosition is on the go board
    if (mousePosition.x >= GO_BOARD_X - GO_BOARD_PADDING \
            && mousePosition.x <= GO_BOARD_X + GO_BOARD_GAP * 14 + GO_BOARD_PADDING \
            && mousePosition.y >= GO_BOARD_Y - GO_BOARD_PADDING \
            && mousePosition.y <= GO_BOARD_Y + GO_BOARD_GAP * 14 + GO_BOARD_PADDING)
    {
        // classify the position near edge
        if (mousePosition.x >= GO_BOARD_X - GO_BOARD_PADDING \
            && mousePosition.x <= GO_BOARD_X)
        {   
            x = 0;
        }
        else if (mousePosition.x >= GO_BOARD_X + GO_BOARD_GAP * 14 \
            && mousePosition.x <= GO_BOARD_X + GO_BOARD_GAP * 14 + GO_BOARD_PADDING)
        {
            x = 14;
        }
        if (mousePosition.y >= GO_BOARD_Y - GO_BOARD_PADDING \
            && mousePosition.y <= GO_BOARD_Y)
        {
            y = 0;
        }
        else if (mousePosition.y >= GO_BOARD_Y + GO_BOARD_GAP * 14 \
            && mousePosition.y <= GO_BOARD_Y + GO_BOARD_GAP * 14 + GO_BOARD_PADDING)
        {
            y = 14;
        }
        // classify the position: rest of the board
        float tmpX = std::roundf(static_cast<float>(mousePosition.x - GO_BOARD_X) / GO_BOARD_GAP);
        float tmpY = std::roundf(static_cast<float>(mousePosition.y - GO_BOARD_Y) / GO_BOARD_GAP);

        // set x, y
        if (x == -1)
            x = static_cast<int>(tmpX);
        if (y == -1)
            y = static_cast<int>(tmpY);
        // temporary stone position: hover over the board
        if (mGameHandler->IsLegalMove(x, y))
        {
            if (mStoneTmpPosition.first != x || mStoneTmpPosition.second != y)
            {
                mGameHandler->SetBannedMove(GameHandler::POSSIBLE);
            }
            if (mGameHandler->CheckRule(x, y))
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) \
                    && AScene::isAnyClickEventHappening == false)
                {
                    if (mGameHandler->PlaceStone(x, y))
                    {
                        std::cout << "Stone placed at " << x << ", " << y << std::endl;
                        mStoneTmpPosition = std::make_pair(-1, -1);
                        AScene::isAnyClickEventHappening = true;
                        return ;
                    }
                }
            }
            mStoneTmpPosition = std::make_pair(x, y);    
            // set sprite(banned move)
            GameHandler::eBannedMove bannedMove = mGameHandler->GetBannedMove();
            if (bannedMove == GameHandler::OPEN_THREE)
            {
                mCurrentTmpStoneSprite = &mTmpStoneSprites[THREE_THREE_BAN_GUI];
            }
            else if (bannedMove == GameHandler::FOUR_FOUR)
            {
                mCurrentTmpStoneSprite = &mTmpStoneSprites[FOUR_FOUR_BAN_GUI];
            }
            else
            {
                if (mGameHandler->GetTurn() == GameHandler::BLACK_TURN)
                {
                    mCurrentTmpStoneSprite = spriteBlackStone;
                }
                else
                {
                    mCurrentTmpStoneSprite = spriteWhiteStone;
                }
            }
        }
        else
        {
            mStoneTmpPosition = std::make_pair(-1, -1);
            return;
        }
    }
}

void PlayLocalScene::DrawStone()
{
    for (auto &stone : mGameHandler->GetBlackStoneHistory())
    {
        spriteBlackStone->setPosition(GO_BOARD_X + stone.first * GO_BOARD_GAP - (static_cast<int>(STONE_RADIUS / 2 * 0.6)), \
                                        GO_BOARD_Y + stone.second * GO_BOARD_GAP - (static_cast<int>(STONE_RADIUS / 2 * 0.6)) );
        mWindow->draw(*spriteBlackStone);
    }
    for (auto &stone : mGameHandler->GetWhiteStoneHistory())
    {
        spriteWhiteStone->setPosition(GO_BOARD_X + stone.first * GO_BOARD_GAP - (static_cast<int>(STONE_RADIUS / 2 * 0.6)), \
                                        GO_BOARD_Y + stone.second * GO_BOARD_GAP - (static_cast<int>(STONE_RADIUS / 2 * 0.6) ));
        mWindow->draw(*spriteWhiteStone);
    }
    // for the temporary stone
    if (mStoneTmpPosition.first != -1)
    {
        mCurrentTmpStoneSprite->setPosition(GO_BOARD_X + mStoneTmpPosition.first * GO_BOARD_GAP - (static_cast<int>(STONE_RADIUS / 2 * 0.6)), \
                                            GO_BOARD_Y + mStoneTmpPosition.second * GO_BOARD_GAP - (static_cast<int>(STONE_RADIUS / 2 * 0.6)));
        mWindow->draw(*mCurrentTmpStoneSprite);
    }

}

void PlayLocalScene::ResetGameHandler()
{
    mGameHandler->ResetGameHandler();
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
    // draw stone
    DrawStone();
}