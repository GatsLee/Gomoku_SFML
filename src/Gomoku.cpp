#include <Gomoku.hpp>

Gomoku::Gomoku()
{
	this->mWindow = new sf::RenderWindow(sf::VideoMode(800, 800), \
										"Gomoku with sfml", sf::Style::Titlebar | sf::Style::Close);
	if (!(*mWindow).isOpen())
	{
		std::cerr << "Error: Could not create window" << std::endl;
		exit(1);
	}
	(*mWindow).setFramerateLimit(60);
	(*mWindow).setVerticalSyncEnabled(true);
	mScenes.push_back(new StartMenuScene(mWindow));
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
		switch (mScenes.back()->GetNextSceneType())
		{
		case AScene::START_MENU:
			mScenes.push_back(new StartMenuScene(mWindow));
			break;
		case AScene::SELECT_MODE:
			mScenes.push_back(new SelectModeScene(mWindow));
			break;
		// case AScene::SELECT_LOCAL:
		// 	mScenes.push(new SelectLocalScene(mWindow));
		// 	break;
		// case AScene::SELECT_AI:
		// 	mScenes.push(new SelectAIScene(mWindow));
		// 	break;
		// case AScene::PAUSE:
		// 	mScenes.push(new PauseScene(mWindow));
		// 	break;
		// case AScene::GAME:
		// 	mScenes.push(new GameScene(mWindow));
		// 	break;
		// case AScene::GAME_OVER:
		// 	mScenes.push(new GameOverScene(mWindow, mCurrentSceneType));
		// 	break;
		case AScene::EXIT:
			exit(0);
			break;
		case AScene::NOT_DEFINED:
			break;
		}
		if (mScenes.back()->IsInit() == false)
		{
			mScenes.back()->Init();
		}
		mScenes.back()->Update(mousePosition, &mScenes, mEvent);
	}
}

void Gomoku::render()
{
	(*mWindow).clear();
	if (!mScenes.empty())
	{
		mScenes.back()->Render();
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
