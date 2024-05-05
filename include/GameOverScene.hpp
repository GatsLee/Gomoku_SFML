#pragma once

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <AScene.hpp>
#include <Button.hpp>
#include <PlayLocalScene.hpp>
// #include <PlayAIScene.hpp>

class GameOverScene : public AScene
{
public:
    GameOverScene(sf::RenderWindow* window);
    ~GameOverScene();

    void Init();
    void Update(const sf::Vector2i &mousePosition, 	std::vector<AScene *> *mScenes, sf::Event event);
    void Render();

private:
    enum eTextureType
    {
        GO_BACKGROUND,
        MODAL_BACKGROUND,
        GAMEOVER_TITLE,
    };

    std::string mWinner;

    sf::Sprite mSprites[3];
    sf::Text *mWinnerText;
    Button *mPlayAgainButton;
    Button *mBackToSelectModeButton;
    Button *mQuitButton;
};