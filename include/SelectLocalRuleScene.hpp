#pragma once

#include "SFML/Graphics/Sprite.hpp"
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <PlayLocalScene.hpp>
#include <AScene.hpp>
#include <Button.hpp>

class SelectLocalRuleScene : public AScene
{
public:
    SelectLocalRuleScene(sf::RenderWindow* window);
    ~SelectLocalRuleScene();

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
        SELECT_TITLE,
    };

    sf::Sprite mSprites[3];
    Button *mFreeRuleButton;
    Button *mStandardRuleButton;
    Button *mRenjuRuleButton;
    Button *mBackButton;
};