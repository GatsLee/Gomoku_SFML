#pragma once

#include "SFML/Window/Event.hpp"
#include <SFML/Graphics.hpp>
#include <Scene.hpp>
// #include "./includes/AI.hpp"
#include <iostream>
#include <stack>

#define START_X 37
#define START_Y 37

#define GAP 70

class Gomoku
{
public:
	Gomoku();
	~Gomoku();

	void render();

	void updateEvents();
	void update();

	void run();

private:
	sf::RenderWindow* mWindow;
	sf::Event mEvent;
	std::stack<Scene *> mScenes;

	int mBoard[15][15] = {0};
};
