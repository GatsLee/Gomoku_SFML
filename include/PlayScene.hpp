#pragma once

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <AScene.hpp>
#include <Button.hpp>
#include <vector>

class PlayScene : public AScene
{
public:
    PlayScene(sf::RenderWindow* window);
    ~PlayScene();

    void Init();
    void Update(const sf::Vector2i &mousePosition, \
                std::vector<AScene *> *mScenes, \
                sf::Event event);
    void Render();

private:
    enum eTextureType
    {
        BLACK_STONE_GUI,
        WHITE_STONE_GUI,
        GO_BOARD,
    };
    
    sf::Sprite mSprites[3];
    Button *mRerollButton;
    Button *mOptionButton;
    Button *mBackButton;

};