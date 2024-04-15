#include <StartMenuScene.hpp>

StartMenuScene::StartMenuScene() : AScene()
{
}

StartMenuScene::~StartMenuScene()
{
}

void StartMenuScene::Init(sf::RenderWindow* window)
{
    mWindow = window;
    mTextures[MENU_BACKGROUND].loadFromFile("asset/texture/GomoKuBackground.png");
    // mTextures[MENU_TITLE].loadFromFile("asset/image/title.png");
    mTextures[MENU_PLAY_BUTTON].loadFromFile("asset/image/GomokuButton.png");
}