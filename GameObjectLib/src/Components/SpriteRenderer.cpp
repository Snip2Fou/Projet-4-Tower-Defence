#include "Components/SpriteRenderer.h"
#include "SFML/Graphics.hpp"


SpriteRenderer::SpriteRenderer()
{
	sprite = new sf::Sprite();
	texture = new sf::Texture();
}

SpriteRenderer::~SpriteRenderer() 
{
	delete sprite;
	delete texture;
	sprite = nullptr;
	texture = nullptr;
}

void SpriteRenderer::SetSprite(sf::Texture* new_texture, float scale_x, float scale_y)
{
	texture = new_texture;
	width = texture->getSize().x * scale_x;
	height = texture->getSize().y * scale_y;
	sprite->setTexture(*texture);
	sprite->setScale(scale_x, scale_y);
}

void SpriteRenderer::Render(sf::RenderWindow* _window) 
{
	Component::Render(_window);

	sprite->setPosition(GetOwner()->GetPosition().GetX(), GetOwner()->GetPosition().GetY());
	_window->draw(*sprite);
}

void SpriteRenderer::SetOrigin(float x, float y)
{
	sprite->setOrigin(x, y);
}