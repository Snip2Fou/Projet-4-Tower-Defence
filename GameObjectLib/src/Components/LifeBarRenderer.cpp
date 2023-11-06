#include "Components/LifeBarRenderer.h"
#include "SFML/Graphics.hpp"
#include "Components/LifeBar.h"


LifeBarRenderer::LifeBarRenderer() 
{
	shape = new sf::RectangleShape();
	shape2 = new sf::RectangleShape();
	sprite = new sf::Sprite();
	texture = new sf::Texture();
}

LifeBarRenderer::~LifeBarRenderer() 
{
	delete shape;
	delete shape2;
	delete sprite;
	delete texture;
	sprite = nullptr;
	texture = nullptr;
	shape = nullptr;
	shape2 = nullptr;
}

void LifeBarRenderer::SetSprite(sf::Texture* new_texture, float scale_x, float scale_y)
{
	texture = new_texture;
	sprite->setTexture(*texture);
	sprite->setScale(scale_x, scale_y);
	sprite->setOrigin(0.0f / 2, 0.0f / 2);
	sprite->setPosition(0.0f, 0);
}

void LifeBarRenderer::Render(sf::RenderWindow* _window)
{
	Component::Render(_window);

	LifeBar* lifebar = GetOwner()->getComponent<LifeBar>();

	shape->setPosition(sprite->getPosition().x + 128, sprite->getPosition().y + 47);
	shape->setSize(sf::Vector2f(148.f*lifebar->GetHp()/lifebar->GetHpMax(), 25.f));
	shape->setOrigin(sf::Vector2f(shape->getPosition().x/2, shape->getPosition().y/2));
	shape->setFillColor(sf::Color::Red);

	shape2->setPosition(sprite->getPosition().x + 128, sprite->getPosition().y + 47);
	shape2->setSize(sf::Vector2f(148.f, 25.f));
	shape2->setOrigin(sf::Vector2f(shape->getPosition().x / 2, shape->getPosition().y / 2));
	shape2->setFillColor(sf::Color(128, 128, 128, 255));

	_window->draw(*shape2);
	_window->draw(*shape);
	_window->draw(*sprite);
}