#pragma once

#include "Component.h"
#include "WindowConfig.h"

class Scene;

class Button : public Component
{
private:
	WindowConfig windowConfig;
	ObjectName name = ObjectName::ButtonName;
	float longueur = 200.f;
	float hauteur = 100.f;

	Maths::Vector2<float> positionPlay = Maths::Vector2<float>(windowConfig.longueur / 2, windowConfig.largeur * 1 / 6);
	sf::Color colorPlay = sf::Color::Blue;
	sf::Color colorPlayHover = sf::Color::White;
	sf::Color colorPlayClick = sf::Color::Yellow;

	Maths::Vector2<float> positionOption = Maths::Vector2<float>(windowConfig.longueur / 2, windowConfig.largeur * 2 / 6);
	sf::Color colorOption = sf::Color::Blue;
	sf::Color colorOptionHover = sf::Color::White;
	sf::Color colorOptionClick = sf::Color::Yellow;

	Maths::Vector2<float> positionAch = Maths::Vector2<float>(windowConfig.longueur / 2, windowConfig.largeur * 3 / 6);
	sf::Color colorAch = sf::Color::Blue;
	sf::Color colorAchHover = sf::Color::White;
	sf::Color colorAchClick = sf::Color::Yellow;

	Maths::Vector2<float> positionQuit = Maths::Vector2<float>(windowConfig.longueur / 2, windowConfig.largeur * 5.5 / 6);
	sf::Color colorQuit = sf::Color::Red;
	sf::Color colorQuitHover = sf::Color::White;
	sf::Color colorQuitClick = sf::Color::Yellow;

	Maths::Vector2<float> positionPause = Maths::Vector2<float>(windowConfig.longueur - 50, 50);
	sf::Color colorPause = sf::Color(93, 93, 93);
	sf::Color colorPauseHover = sf::Color(27, 27, 27);
	sf::Color colorPauseClick = sf::Color(93, 93, 93);
	sf::Vector2f sizePause = sf::Vector2f(hauteur / 2, hauteur / 2);

	Maths::Vector2<float> positionBuildMenu = Maths::Vector2<float>(12.5, windowConfig.largeur-12.5);
	sf::Color colorBuildMenu = sf::Color(255, 255, 255);
	sf::Color colorBuildMenuHover = sf::Color(27, 27, 27);
	sf::Color colorBuildMenuClick = sf::Color(93, 93, 93);
	sf::Vector2f sizeBuildMenu = sf::Vector2f(25, 25);

	Maths::Vector2<float> positionButtonTower1 = Maths::Vector2<float>(50, windowConfig.largeur + 50);
	Maths::Vector2<float> positionButtonTower2 = Maths::Vector2<float>(150, windowConfig.largeur + 50);
	Maths::Vector2<float> positionButtonTower3 = Maths::Vector2<float>(250, windowConfig.largeur + 50);
	sf::Color colorButtonTower = sf::Color::Red;
	sf::Color colorButtonTowerHover = sf::Color::Blue;
	sf::Color colorButtonTowerClick = sf::Color::Cyan;
	sf::Vector2f sizeButtonTower = sf::Vector2f(75, 75);


public:
	std::string type = "";

	sf::Color color = sf::Color::Transparent;
	sf::Color colorNothing = sf::Color::Transparent;
	sf::Color colorHover = sf::Color::Transparent;
	sf::Color colorClick = sf::Color::Transparent;

	sf::Vector2f Size = sf::Vector2f(longueur, hauteur);
	Maths::Vector2<float> position = Maths::Vector2<float>(0, 0);

	bool is_selected = false;
	bool is_activate = true;

	GameObject* createButtonObj(Scene* scene, std::string type);
	void Update(float DeltaTimeMillisecondes, std::vector<GameObject*>* gameObject) override;
};
