#include "Components/Component.h"

Component::Component(GameObject* owner)
{
	this->owner = owner;
}

void Component::Update(float deltaTimeMillisecondes, std::vector<GameObject*>* gameObjects) {}

void Component::Render(sf::RenderWindow* _window) {}
