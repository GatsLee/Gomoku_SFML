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
		// GAME SCENE
		case AScene::START_MENU:
			mScenes.push_back(new StartMenuScene(mWindow));
			break;
		case AScene::SELECT_MODE:
			mScenes.push_back(new SelectModeScene(mWindow));
			break;
		case AScene::SELECT_LOCAL_RULE:
			mScenes.push_back(new SelectLocalRuleScene(mWindow));
			break;
		case AScene::SELECT_AI_RULE:
			mScenes.push_back(new SelectAIRuleScene(mWindow));
			break;
		case AScene::SELECT_AI_STONE:
			mScenes.push_back(new SelectAIStoneScene(mWindow));
			break;
		case AScene::PLAY_LOCAL:
			mScenes.push_back(new PlayLocalScene(mWindow));
			break;
		case AScene::PLAY_AI:
			mScenes.push_back(new PlayAIScene(mWindow));
			break;
		case AScene::EXIT:
			exit(0);
			break;
		case AScene::NOT_DEFINED:
			break;
		case AScene::GAME_OVER:
			mScenes.push_back(new GameOverScene(mWindow));
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
