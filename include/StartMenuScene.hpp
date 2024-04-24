#pragma once

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <AScene.hpp>
#include <Button.hpp>
#include <iostream>

class StartMenuScene : public AScene
{
public:
    StartMenuScene(sf::RenderWindow* window);
    ~StartMenuScene();

    void Init();
    void Update(const sf::Vector2i &mousePosition, \
                    std::vector<AScene *> *mScenes, \
                    sf::Event event);
    void Render();
private:
    enum eTextureType
    {
        GO_BACKGROUND,
        MODAL_BACKGROUND,
        MENU_TITLE,
    };

    sf::Sprite mSprites[3];
    sf::Text *mMakerText;
    Button* mPlayButton;
    Button* mExitButton;
};