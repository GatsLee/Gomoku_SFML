#pragma once

#include <AScene.hpp>
#include <Button.hpp>
#include <map>
#include <iostream>

class StartMenuScene : public AScene
{
public:
    StartMenuScene();
    ~StartMenuScene();

    void Init(sf::RenderWindow* window);
    void Update();
    void Render();
    void HandleInput();
private:
    enum eTextureType
    {
        MENU_BACKGROUND,
        MENU_TITLE,
        MENU_PLAY_BUTTON,
    };

    sf::Texture mTextures[3];
    std::map<std::string, Button *> mButtons;
};