#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>

class AScene
{
public:
    enum eSceneType
    {
        START_MENU,
        SELECT_MODE,
        SELECT_AI,
        PLAY_LOCAL,
        PAUSE,
        GAME_LOCAL,
        GAME_AI,
        GAME_OVER,
        NOT_DEFINED,
        EXIT
    };

public:
    AScene(eSceneType sceneType, sf::RenderWindow* window);
    virtual ~AScene();

    virtual void Init() = 0;
    virtual void Update(const sf::Vector2i &mousePosition, 	std::vector<AScene *> *mScenes, sf::Event event) = 0;
    virtual void Render() = 0;

    AScene::eSceneType GetSceneType() const;
    AScene::eSceneType GetNextSceneType() const;

    bool IsInit() const;
    void SetIsInit(bool isInit);

    bool IsRunning() const;
    void SetIsRunning(bool isRunning);

    bool IsAnySceneRunning(std::vector<AScene *> *mScenes);

    void SetNextSceneType(eSceneType nextSceneType);
protected:
    eSceneType mSceneType;
    eSceneType mNextSceneType;
    sf::View mView;
    sf::RenderWindow* mWindow;

    bool mIsInit;
    bool mIsRunning;
};