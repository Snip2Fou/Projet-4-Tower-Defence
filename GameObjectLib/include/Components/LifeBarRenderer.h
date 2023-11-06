#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include "SFML/Graphics/Sprite.hpp"
#include "Component.h"

class LifeBarRenderer : public Component
{
public:
	LifeBarRenderer();
	~LifeBarRenderer() override;

	void SetSprite(sf::Texture* new_texture, float scale_x, float scale_y);

	void Render(sf::RenderWindow* _window) override;

private:
	sf::RectangleShape* shape = nullptr;
	sf::RectangleShape* shape2 = nullptr;
	sf::Sprite* sprite = nullptr;
	sf::Texture* texture = nullptr;
};