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

}

void PlayAIScene::Update(const sf::Vector2i& mousePosition, std::vector<AScene*>* mScenes, sf::Event event)
{
    if (IsAnySceneRunning(mScenes) == false)
    {
        SetIsRunning(true);
    }
}

void PlayAIScene::Render()
{
    mWindow->clear();
    mWindow->display();
}