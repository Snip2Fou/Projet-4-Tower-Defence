#pragma once

#include "Component.h"
#include "SFML/Graphics/Sprite.hpp"

class SpriteRenderer : public Component
{
public:
	SpriteRenderer();
	~SpriteRenderer() override;

	float GetHeight() const { return height; }
	float GetWidth() const { return width; }
	void SetWidth(const float _width) { width = _width; }
	void SetHeight(const float _height) { height = _height; }
	void SetOrigin(float x, float y);
	sf::Sprite* GetSprite() { return sprite; }
	void SetSprite(sf::Texture* new_texture, float scale_x, float scale_y);

	void Render(sf::RenderWindow* _window) override;

private:
	sf::Sprite* sprite = nullptr;
	sf::Texture* texture = nullptr;
	int width = 100;
	int height = 100;
};
