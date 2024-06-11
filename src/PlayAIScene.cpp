#include <PlayAIScene.hpp>

int PlayAIScene::AIRuleSetting = 0;
int PlayAIScene::AITurn = 0;

PlayAIScene::PlayAIScene(sf::RenderWindow* window)
    : AScene(PLAY_AI, window)
{}

PlayAIScene::~PlayAIScene()
{}

void PlayAIScene::Init()
{
    // Set the game handler
    mGameHandler = new GameHandler(static_cast<enum GameHandler::eGameRule>(AIRuleSetting), \
    GameHandler::MODE_AI, AITurn);

    // set Sprites
    sf::Texture *textureGoBoard, *textureWhiteGui, *textureBlackGui;
    textureGoBoard = new sf::Texture();
    textureWhiteGui = new sf::Texture();
    textureBlackGui = new sf::Texture();
    if (!textureGoBoard->loadFromFile("asset/texture/GoBan.png")
        || !textureWhiteGui->loadFromFile("asset/texture/WhiteStoneGui.png")
        || !textureBlackGui->loadFromFile("asset/texture/BlackStoneGui.png"))
    {
        std::cerr << "Error: Could not load texture for Play Local Scene" << std::endl;
        exit(1);
    }
    mSprites[GO_BOARD].setTexture(*textureGoBoard);
    mSprites[WHITE_STONE_GUI].setTexture(*textureWhiteGui);
    mSprites[BLACK_STONE_GUI].setTexture(*textureBlackGui);

    mSprites[GO_BOARD].setScale(0.6, 0.6);
    mSprites[GO_BOARD].setPosition(80,140);
    mSprites[WHITE_STONE_GUI].setPosition(30, 15);
    mSprites[BLACK_STONE_GUI].setPosition(530, 15);

    mSprites[WHITE_STONE_GUI].setScale(0.8, 0.8);
    mSprites[BLACK_STONE_GUI].setScale(0.8, 0.8);

    sf::Font *font = new sf::Font();
    if (!font->loadFromFile("asset/font/joystix_monospace.otf"))
    {
        std::cerr << "Error: Could not load font for Play Local Scene" << std::endl;
        exit(1);
    }
    std::string tmpPlayerOne = (AITurn == 0) ? "AI": "Player";
    std::string tmpPlayerTwo = (AITurn == 0) ? "Player": "AI";

    mPlayerOneName = new sf::Text(tmpPlayerOne, *font, 25);
    mPlayerTwoName = new sf::Text(tmpPlayerTwo, *font, 25);

    mPlayerOneName->setFillColor(sf::Color::Black);
    mPlayerTwoName->setFillColor(sf::Color::Black);
    mPlayerOneName->setPosition(mSprites[WHITE_STONE_GUI].getGlobalBounds().getPosition().x + 63, \
                                 mSprites[WHITE_STONE_GUI].getGlobalBounds().getPosition().y + 10);
    mPlayerTwoName->setPosition(mSprites[BLACK_STONE_GUI].getGlobalBounds().getPosition().x + 63, \
                                    mSprites[BLACK_STONE_GUI].getGlobalBounds().getPosition().y + 10);
    
    //set background
    mWhiteBackground.setSize(sf::Vector2f(800, 800));
    mWhiteBackground.setFillColor(sf::Color::White);

    // set stone sprite
    sf::Texture *textureBlackStone = new sf::Texture();
    sf::Texture *textureWhiteStone = new sf::Texture();
    if (!textureBlackStone->loadFromFile("asset/texture/BlackStone2.png")
        || !textureWhiteStone->loadFromFile("asset/texture/WhiteStone2.png"))
    {
        std::cerr << "Error: Could not load texture for Play Local Scene" << std::endl;
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

void PlayAIScene::Update(const sf::Vector2i& mousePosition, std::vector<AScene*>* mScenes, sf::Event event)
{
    if (IsAnySceneRunning(mScenes) == false)
    {
        SetIsRunning(true);
        if (event.type == sf::Event::MouseButtonReleased)
        {
            AScene::isAnyClickEventHappening = false;
        }

        UpdateStone(mousePosition);
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

void PlayAIScene::UpdateStone(const sf::Vector2i &mousePosition)
{
    int x = -1, y = -1;

    // for player's turn
    if (mGameHandler->GetTurn() != mGameHandler->GetAITurn())
    {
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
    else // for AI's turn
    {
        // 1. show AI is thinking
        // 2. show AI's possible stone
        // 3. place AI's stone
    }
}

void PlayAIScene::DrawStone()
{
    // AI's turn: draw the possible stones after AI's calculation: elapsed time
    if (mGameHandler->GetTurn() == mGameHandler->GetAITurn())
    {
        // draw the possible stones
        // draw the AI's stone
    }
    // draw the go stones: distinguish the stone color: player & AI
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
    // for the temporary stone: player's turn
    if (mStoneTmpPosition.first != -1)
    {
        mCurrentTmpStoneSprite->setPosition(GO_BOARD_X + mStoneTmpPosition.first * GO_BOARD_GAP - (static_cast<int>(STONE_RADIUS / 2 * 0.6)), \
                                            GO_BOARD_Y + mStoneTmpPosition.second * GO_BOARD_GAP - (static_cast<int>(STONE_RADIUS / 2 * 0.6)));
        mWindow->draw(*mCurrentTmpStoneSprite);
    }
}

void PlayAIScene::ResetGameHandler()
{
    mGameHandler->ResetGameHandler();
}

void PlayAIScene::Render()
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
    // draw AI related animation & possible stones
    
    // draw stones
    DrawStone();
}