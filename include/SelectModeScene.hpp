#pragma once

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <AScene.hpp>
#include <Button.hpp>
#include <iostream>

class SelectMenuScene : public AScene
{
public:
    SelectMenuScene(sf::RenderWindow* window, AScene::eSceneType &mCurrentSceneType);
    ~SelectMenuScene();

    void Init();
    void Update(const sf::Vector2i &mousePosition);
    void Render();
private:

    Button *mPlayLocalButton;
    Button *mPlayAIButton;
    Button *mBackButton;
};