#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <StartMenuScene.hpp>
#include <SelectModeScene.hpp>
#include <SelectLocalRuleScene.hpp>
#include <SelectAIRuleScene.hpp>
#include <SelectAIStoneScene.hpp>
#include <PlayLocalScene.hpp>
#include <PlayAIScene.hpp>
#include <GameOverScene.hpp>
#include <iostream>
#include <vector>

class Gomoku
{
public:
	Gomoku();
	~Gomoku();

	void render();

	void updateEvents();
	void update();

	void run();

public:
	enum eUtilUnit
	{
		START_X = 37,
		START_Y = 37,
		GAP = 70,
	};

private:
	sf::RenderWindow* mWindow;
	sf::Event mEvent;
	std::vector<AScene *> mScenes;
};
