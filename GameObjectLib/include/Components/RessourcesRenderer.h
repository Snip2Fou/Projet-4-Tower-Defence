#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include "SFML/Graphics/Sprite.hpp"
#include "Component.h"

class RessourcesRenderer : public Component
{
public:
	RessourcesRenderer();
	~RessourcesRenderer();

	void SetSprite(sf::Texture* new_texture, float scale_x, float scale_y);
	void Render(sf::RenderWindow* _window) override;

private:
	sf::Sprite* sprite = nullptr;
	sf::Texture* texture = nullptr;
};
