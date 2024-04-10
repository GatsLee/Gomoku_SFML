#pragma once

#include "SFML/Window/Event.hpp"
#include <SFML/Graphics.hpp>
#include <IScene.hpp>
#include <iostream>
#include <stack>

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
	std::stack<IScene *> mScenes;
};
