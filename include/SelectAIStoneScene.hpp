#pragma once

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <AScene.hpp>
#include <Button.hpp>

class SelectAIStoneScene : public AScene
{
public:

private:
    enum eTextureType
    {
        GO_BACKGROUND,
        MODAL_BACKGROUND,
        SELECT_TITLE,
    };

    sf::Sprite mSprites[3];
    Button *mBlackStoneButton;
    Button *mWhiteStoneButton;
    Button *mBackButton;

    sf::Text *mBlackStoneText;
    sf::Text *mWhiteStoneText;

};