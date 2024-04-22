#include <AScene.hpp>

AScene::AScene(eSceneType sceneType, sf::RenderWindow* window)
    : mSceneType(sceneType), mNextSceneType(NOT_DEFINED) ,mWindow(window)
{
    mView.setSize(1080, 1080);
    mView.setCenter(1080, 1080);
    mFont.loadFromFile("asset/font/joystix_monospace.otf");
};

AScene::~AScene()
{};

AScene::eSceneType AScene::GetSceneType() const
{
    return mSceneType;
}

AScene::eSceneType AScene::GetNextSceneType() const
{
    return mNextSceneType;
}

void AScene::SetNextSceneType(eSceneType nextSceneType)
{
    mNextSceneType = nextSceneType;
}