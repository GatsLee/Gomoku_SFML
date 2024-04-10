#include <includes/Gomoku.hpp>

Gomoku::Gomoku()
{
	mWindow.create(sf::VideoMode(1080, 1080), "Gomoku with sfml", sf::Style::Titlebar | sf::Style::Close);
	mWindow.setVerticalSyncEnabled(true);
}

Gomoku::~Gomoku()
{
	mWindow.close();
}

void Gomoku::run()
{
	sf::Texture background;
	if (!background.loadFromFile("./asset/goExtended.png"))
	{
		std::cerr << "Error loading background.png" << std::endl;
		return;
	}

	while (mWindow.isOpen())
	{
		sf::Event event;
		while (mWindow.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					mWindow.close();
					break;

				case sf::Event::MouseButtonPressed:
					break;
				case sf::Event::

				default:
					break;
			}
		}

		mWindow.clear();
		// start with click start button or press
		// else press escape button or close button to exit

		// select mode : 1 player with AI or 2 player in one computer

		// draw background




		mWindow.display();
	}
}


