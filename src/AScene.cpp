#include <AScene.hpp>

AScene::AScene()
{
    mView.setSize(1080, 1080);
    mView.setCenter(1080, 1080);
    mFont.loadFromFile("asset/font/joystix_monospace.ttf");
    mPaused = false;
    mIsRunning = true;
};

AScene::~AScene()
{
};