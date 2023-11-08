#pragma once

#include "eventMenu.h"

class Scenes
{
public:
	virtual int LoopGame(sf::RenderWindow* window, bool pause) { return 0; };
};

class SceneGame : public Scenes
{
public :
	int LoopGame(sf::RenderWindow* window, bool pause) override;
};

class SceneMenu : public Scenes
{
private :
	bool shapeAlpha = false;
public :
	int LoopGame(sf::RenderWindow* window, bool pause) override;
};
