#include "Components/TowerSpot.h"
#include "Scene.h"

GameObject* TowerSpot::createButtonObj(Scene* scene, std::string type)
{
	if (type == "1")
	{
		GameObject* button = scene->CreateButton(name, position1, color1, color1Hover, color1Click, Size, type);
		return button;
	}
	else if (type == "2")
	{
		GameObject* button = scene->CreateButton(name, position2, color2, color2Hover, color2Click, Size, type);
		return button;
	}
	else if (type == "3")
	{
		GameObject* button = scene->CreateButton(name, position3, color3, color3Hover, color3Click, Size, type);
		return button;
	}
	else
	{
		GameObject* buttonBroken = nullptr;
		return buttonBroken;
	}
}

void TowerSpot::Update(float deltaTimeMillisecondes, std::vector<GameObject*>* gameObjects) {

}
