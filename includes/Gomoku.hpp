#pragma once

#include <SFML/Graphics.hpp>
// #include "./includes/AI.hpp"
#include <iostream>

#define START_X 37
#define START_Y 37

#define GAP 70

class Gomoku
{
public:
	Gomoku();
	~Gomoku();

	void run();

public:
	void printCurrentBoard() const;

private:
	sf::RenderWindow mWindow;


	int mBoard[15][15] = {0};



};
