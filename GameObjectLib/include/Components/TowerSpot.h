#pragma once

#include "Component.h"
#include "WindowConfig.h"

class Scene;

class TowerSpot : public Component
{
private:
	WindowConfig windowConfig;
	ObjectName name = ObjectName::ButtonName;
	float longueur = 50.f;
	float hauteur = 50.f;

	Maths::Vector2<float> position1 = Maths::Vector2<float>(windowConfig.longueur / 6, windowConfig.largeur * 2.5 / 6);
	sf::Color color1 = sf::Color::Blue;
	sf::Color color1Hover = sf::Color::White;
	sf::Color color1Click = sf::Color::Yellow;

	Maths::Vector2<float> position2 = Maths::Vector2<float>(windowConfig.longueur / 1.9, windowConfig.largeur * 1.5 / 6);
	sf::Color color2 = sf::Color::Blue;
	sf::Color color2Hover = sf::Color::White;
	sf::Color color2Click = sf::Color::Yellow;

	Maths::Vector2<float> position3 = Maths::Vector2<float>(windowConfig.longueur / 1.4, windowConfig.largeur * 4.5 / 6);
	sf::Color color3 = sf::Color::Blue;
	sf::Color color3Hover = sf::Color::White;
	sf::Color color3Click = sf::Color::Yellow;

public:
	std::string type = "";

	sf::Color color = sf::Color::Transparent;
	sf::Color colorNothing = sf::Color::Transparent;
	sf::Color colorHover = sf::Color::Transparent;
	sf::Color colorClick = sf::Color::Transparent;

	sf::Vector2f Size = sf::Vector2f(longueur, hauteur);
	Maths::Vector2<float> position = Maths::Vector2<float>(0, 0);

	GameObject* createButtonObj(Scene* scene, std::string type);
	void Update(float DeltaTimeMillisecondes, std::vector<GameObject*>* gameObject) override;
};
