#include <Gomoku.hpp>

Gomoku::Gomoku()
{
	this->mWindow = new sf::RenderWindow(sf::VideoMode(1080, 1080), "Gomoku with sfml", sf::Style::Titlebar | sf::Style::Close);
	(*mWindow).setVerticalSyncEnabled(true);
	(*mScenes).push(new StartMenuScene());
	(*mScenes).top()->init(mWindow);
}

Gomoku::~Gomoku()
{
	(*mWindow).close();
}

void Gomoku::update()
{
	while ((*mWindow).pollEvent(mEvent))
	{
		if (mEvent.type == sf::Event::Closed)
		{
			(*mWindow).close();
		}
	}
	if (!mScenes.empty())
	{
		mScenes.top()->update();
	}
}

void Gomoku::render()
{
	(*mWindow).clear();
	if (!mScenes.empty())
	{
		mScenes.top()->render();
	}
	(*mWindow).display();
}

void Gomoku::run()
{
	while ((*mWindow).isOpen())
	{
		Gomoku::update();
		Gomoku::render();
	}
}
