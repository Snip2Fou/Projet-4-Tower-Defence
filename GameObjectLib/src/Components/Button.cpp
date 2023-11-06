#include "Components/Button.h"

#include "Scene.h"

GameObject* Button::createButtonObj(Scene* scene, std::string type)
{
	if (type == "Play")
	{
		GameObject* button = scene->CreateButton(name, positionPlay, colorPlay, colorPlayHover, colorPlayClick, Size, type);
		return button;
	}
	else if (type == "Option")
	{
		GameObject* button = scene->CreateButton(name, positionOption, colorOption, colorOptionHover, colorOptionClick, Size, type);
		return button;
	}
	else if (type == "Quit")
	{
		GameObject* button = scene->CreateButton(name, positionQuit, colorQuit, colorQuitHover, colorQuitClick, Size, type);
		return button;
	}
	else if (type == "Ach")
	{
		GameObject* button = scene->CreateButton(name, positionAch, colorAch, colorAchHover, colorAchClick, Size, type);
		return button;
	}
	else if (type == "Pause")
	{
		GameObject* button = scene->CreateButton(name, positionPause, colorPause, colorPauseHover, colorPauseClick, sizePause, type);
		return button;
	}
	else
	{
		GameObject* buttonBroken = nullptr;
		return buttonBroken;
	}
}

void Button::Update(float deltaTimeMillisecondes, std::vector<GameObject*>* gameObjects) {

}
