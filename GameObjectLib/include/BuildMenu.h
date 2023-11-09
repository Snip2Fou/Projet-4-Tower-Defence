#pragma once
#include "GameObject.h"

class BuildMenu
{
public:

	BuildMenu();
	bool isvisible = false;
	void Update(GameObject* buttonBuildMenu);
	void Render(sf::RenderWindow* _window);
	void SetButtonTower1(GameObject* new_button_tower1) { button_tower1 = new_button_tower1; }
	void SetButtonTower2(GameObject* new_button_tower2) { button_tower2 = new_button_tower2; }
	void SetButtonTower3(GameObject* new_button_tower3) { button_tower3 = new_button_tower3; }

	GameObject* GetButtonTower1() { return button_tower1; }
	GameObject* GetButtonTower2() { return button_tower2; }
	GameObject* GetButtonTower3() { return button_tower3; }

private:
	Maths::Vector2f position = Maths::Vector2f(0, 800);
	sf::Color color = sf::Color::Color(50,50,50);
	sf::Vector2f size = sf::Vector2f(300, 100);
	sf::Vector2f origin = sf::Vector2f(size.x / 2, size.y / 2);
	sf::RectangleShape* shape = nullptr;

	GameObject* button_tower1 = nullptr;
	GameObject* button_tower2 = nullptr;
	GameObject* button_tower3 = nullptr;
};