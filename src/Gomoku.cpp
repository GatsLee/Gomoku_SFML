#include <Gomoku.hpp>

Gomoku::Gomoku()
{
	this->mWindow = new sf::RenderWindow(sf::VideoMode(800, 800), "Gomoku with sfml", sf::Style::Titlebar | sf::Style::Close);
	if (!(*mWindow).isOpen())
	{
		std::cerr << "Error: Could not create window" << std::endl;
		exit(1);
	}
	(*mWindow).setFramerateLimit(60);
	(*mWindow).setVerticalSyncEnabled(true);
	mCurrentSceneType = AScene::START_MENU;
	mScenes.push(new StartMenuScene(mWindow, mCurrentSceneType));
	mScenes.top()->Init();
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
		sf::Vector2i mousePosition = sf::Mouse::getPosition(*mWindow);
		mScenes.top()->Update(mousePosition);
	}
}

void Gomoku::render()
{
	(*mWindow).clear();
	if (!mScenes.empty())
	{
		mScenes.top()->Render();
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
