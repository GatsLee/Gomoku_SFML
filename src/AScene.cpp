#include <AScene.hpp>

bool AScene::isAnyClickEventHappening = false;

AScene::AScene(eSceneType sceneType, sf::RenderWindow* window)
    : mSceneType(sceneType)
    , mNextSceneType(NOT_DEFINED)
    , mWindow(window)
    , mIsInit(false)
{
    mView.setSize(1080, 1080);
    mView.setCenter(1080, 1080);
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

bool AScene::IsInit() const
{
    return mIsInit;
}

void AScene::SetIsInit(bool isInit)
{
    mIsInit = isInit;
}

bool AScene::IsRunning() const
{
    return mIsRunning;
}

void AScene::SetIsRunning(bool isRunning)
{
    mIsRunning = isRunning;
}

bool AScene::IsAnySceneRunning(std::vector<AScene *> *mScenes)
{
    bool anySceneRunning = false;
    for (auto scene : *mScenes)
    {
        if (scene->IsRunning() && scene->GetSceneType() != this->GetSceneType())
        {
            std::cout << "Scene " << scene->GetSceneType() << " is running" << std::endl;
            anySceneRunning = true;
            break;
        }
    }
    return anySceneRunning;
}