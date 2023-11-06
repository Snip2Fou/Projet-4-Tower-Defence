#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include "Component.h"

class ShapeRenderer : public Component
{
public:
	ShapeRenderer();
	~ShapeRenderer() override;

	void SetColor(const sf::Color& _color) { color = _color; }
	void SetSize(const sf::Vector2f _size) { size = _size; origin = sf::Vector2f(size.x / 2, size.y / 2); }

	void Render(sf::RenderWindow* _window) override;

private:
	sf::Color color = sf::Color::White;
	sf::Vector2f size = sf::Vector2f(50, 50);
	sf::Vector2f origin = sf::Vector2f(size.x/2, size.y/2);
	sf::RectangleShape* shape = nullptr;
};
