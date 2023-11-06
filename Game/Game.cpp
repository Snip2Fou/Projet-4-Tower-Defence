#include "Game.h"

int Game::gameOn() {
	SceneMenu sceneMenu;
	SceneGame sceneGame;

	auto window = new sf::RenderWindow(sf::VideoMode(this->largeur, this->longueur), "Game", sf::Style::Titlebar | sf::Style::Close);
	window->setFramerateLimit(this->frameRateLimit);

	while (window->isOpen())
	{
		int loopMenuToChangeScene = sceneMenu.LoopGame(window);
		while ((loopMenuToChangeScene != (-1)) && (loopMenuToChangeScene != 4))
		{
			

			// Game On
			if (loopMenuToChangeScene == 1)
			{
				int GameIsOn = sceneGame.LoopGame(window);
				//Erreur
				if (GameIsOn == 1)
				{
					return 1;
				}
			}

			// Option
			else if (loopMenuToChangeScene == 2)
			{
				std::cout << "J'étais à la PGW, pas eu le temps" << std::endl << "Options" << std::endl;
			}

			// Achievement
			else if (loopMenuToChangeScene == 3)
			{
				std::cout << "J'étais à la PGW, pas eu le temps" << std::endl <<  "Achievement" << std::endl;
			}

			loopMenuToChangeScene = sceneMenu.LoopGame(window);
		}

		// Erreur
		if (loopMenuToChangeScene == -1)
		{
			return 1;
		} 

		// Quit Game
		else if (loopMenuToChangeScene == 3)
		{
			return 0;
		}
		
	}
	return 0;

}