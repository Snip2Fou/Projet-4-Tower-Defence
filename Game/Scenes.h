#pragma once

#include "eventMenu.h"

class Scenes
{
public:
	virtual int LoopGame(sf::RenderWindow* window) { return 0; };
};

class SceneGame : public Scenes
{
public :
	int LoopGame(sf::RenderWindow* window) override;
};

class SceneMenu : public Scenes
{
public :
	int LoopGame(sf::RenderWindow* window) override;
};
