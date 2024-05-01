#pragma once

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <AScene.hpp>
#include <Button.hpp>
#include <GameHandler.hpp>
#include <vector>

class PlayLocalScene : public AScene
{
public:
    PlayLocalScene(sf::RenderWindow* window);
    ~PlayLocalScene();

    void Init();
    void Update(const sf::Vector2i &mousePosition, \
                std::vector<AScene *> *mScenes, \
                sf::Event event);
    void Render();

    static int LocalRuleSetting;
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