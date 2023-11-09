#include "Components/RessourcesRenderer.h"
#include "Components/Ressources.h"

RessourcesRenderer::RessourcesRenderer()
{
	sprite = new sf::Sprite();
	texture = new sf::Texture();
}

RessourcesRenderer::~RessourcesRenderer()
{
	delete sprite;
	delete texture;
	sprite = nullptr;
	texture = nullptr;
}

void RessourcesRenderer::SetSprite(sf::Texture* new_texture, float scale_x, float scale_y)
{
	texture = new_texture;
	sprite->setTexture(*texture);
	sprite->setScale(scale_x, scale_y);
	sprite->setOrigin(0.0f / 2, 0.0f / 2);
	sprite->setPosition(0.0f, 0);
}

void RessourcesRenderer::Render(sf::RenderWindow* _window)
{
	Component::Render(_window);

	Ressources* ressource = GetOwner()->getComponent<Ressources>();

	_window->draw(*sprite);

}