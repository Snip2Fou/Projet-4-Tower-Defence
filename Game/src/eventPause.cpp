#include "eventPause.h"
#include "Scenes.h"

int EventFunctionPause::loopEvent(sf::RenderWindow* window, bool* pauseOn) {
	SceneMenu sceneMenu;

	int temp = sceneMenu.LoopGame(window, pauseOn);
	while (pauseOn)
	{
		if (temp == 1)
		{
			*pauseOn = false;
			return 0;
		}
		if (temp == 0)
		{
			*pauseOn = false;
			return -1;
		}
		if (temp == 2)
		{
			std::cout << "helo";
		}
		if (temp == 3)
		{
			std::cout << "halo";
		}
		temp = sceneMenu.LoopGame(window, pauseOn);
	}
	return 0;
}