#include "eventMenu.h"
#include "button.h"
#include "ShapeRenderer.h"

void EventFunctionsMenu::eventCloseWindow(sf::RenderWindow* window) {
	window->close();
}

void EventFunctionsMenu::eventChangeColorButton(GameObject* buttonCheck, sf::Color colorChange) {
	Button* buttonCheckButton = buttonCheck->getComponent<Button>();
	ShapeRenderer* buttonCheckShape = buttonCheck->getComponent<ShapeRenderer>();

	buttonCheckButton->color = colorChange;
	buttonCheckShape->SetColor(colorChange);
}

int EventFunctionsMenu::eventCheckClickButton(sf::Vector2i mousePosition, sf::Event event, sf::RenderWindow* window) {
	std::vector<std::string> returnWhat;

	for (GameObject* buttonCheck : buttonList)
	{
		 returnWhat.push_back(eventClickButton(buttonCheck, mousePosition));
	}

	for (std::string returnWhatBool : returnWhat)
	{
		if (returnWhatBool == "Play") {
			return 1;
		}
		else if (returnWhatBool == "Option")
		{
			return 2;
		}
		else if (returnWhatBool == "Ach")
		{
			return 3;
		}
		else if (returnWhatBool == "Quit")
		{
			eventCloseWindow(window);
			return 4;
		}
	}
	return 0;
}

bool EventFunctionsMenu::eventCollisionMouseButton(GameObject* buttonCheck, sf::Vector2i mousePosition) {
	Button* buttonCheckButton = buttonCheck->getComponent<Button>();

	sf::Vector2f position(buttonCheckButton->position.x, buttonCheckButton->position.y);
	float hauteur = buttonCheckButton->Size.y;
	float largeur = buttonCheckButton->Size.x;
	sf::Vector2f ShapeStart(position.x - largeur / 2, position.y - hauteur / 2);
	sf::Vector2f ShapeEnd(ShapeStart.x + largeur, ShapeStart.y + hauteur);

	if (
		(mousePosition.x > ShapeStart.x) && (mousePosition.x < ShapeEnd.x) &&
		(mousePosition.y > ShapeStart.y) && (mousePosition.y < ShapeEnd.y)
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}


void EventFunctionsMenu::eventHoverButton(GameObject* buttonCheck, sf::Vector2i mousePosition) {
	Button* buttonCheckButton = buttonCheck->getComponent<Button>();

	if (eventCollisionMouseButton(buttonCheck, mousePosition) == true)
	{
		eventChangeColorButton(buttonCheck, buttonCheckButton->colorHover);
	}
	else
	{
		eventChangeColorButton(buttonCheck, buttonCheckButton->colorNothing);
	}
	
}

std::string EventFunctionsMenu::eventClickButton(GameObject* buttonCheck, sf::Vector2i mousePosition) {
	Button* buttonCheckButton = buttonCheck->getComponent<Button>();

	if (eventCollisionMouseButton(buttonCheck, mousePosition) == true)
	{
		eventChangeColorButton(buttonCheck, buttonCheckButton->colorClick);
		return buttonCheckButton->type;
	}
	return "";
}

int EventFunctionsMenu::loopEvent(sf::RenderWindow* window) {

	sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
	for (GameObject* buttonCheck : buttonList)
	{
		eventHoverButton(buttonCheck, mousePosition);
	}

	sf::Event event;
	while (window->pollEvent(event)) {
		if (event.type == sf::Event::Closed)
		{
			eventCloseWindow(window);
			return 3;
		}

		else if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (eventCheckClickButton(mousePosition, event, window) != 0)
				{
					return eventCheckClickButton(mousePosition, event, window);
				}
			}
		}
	}

	return 0;
}