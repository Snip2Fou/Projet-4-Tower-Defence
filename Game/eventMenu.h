#pragma once
#include "event.h"

class EventFunctionsMenu {
public:
	std::vector<GameObject*> buttonList;

	void eventChangeColorButton(GameObject* buttonCheck, sf::Color colorChange);
	int eventCheckClickButton(sf::Vector2i mousePosition, sf::Event event, sf::RenderWindow* window);
	bool eventCollisionMouseButton(GameObject* buttonCheck, sf::Vector2i mousePosition);

	void eventCloseWindow(sf::RenderWindow* window);
	void eventHoverButton(GameObject* buttonCheck, sf::Vector2i mousePosition);
	std::string eventClickButton(GameObject* buttonCheck, sf::Vector2i mousePosition);

	int loopEvent(sf::RenderWindow* window);
};