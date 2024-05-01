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
    // set Sprites
    sf::Texture *textureGoBackground, *textSelectTitle, *textModalBackground;
}