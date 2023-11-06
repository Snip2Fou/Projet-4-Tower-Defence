#include "GameObject.h"
#include "SFML/Graphics.hpp"

#include "Scene.h"

void GameObject::AddComponent(Component* _component)
{
	_component->SetOwner(this);
	components.push_back(_component);
}

void GameObject::RemoveComponent(Component* _component)
{
	components.erase(std::remove(components.begin(), components.end(), _component), components.end());
}

void GameObject::Update(float deltaTimeMillisecondes, std::vector<GameObject*>* gameObjects) const
{
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->Update(deltaTimeMillisecondes, gameObjects);
	}
}

void GameObject::Render(sf::RenderWindow* _window) const
{
	for (Component* const& component : components)
	{
		component->Render(_window);
	}
}

sf::FloatRect GameObject::getBounds(sf::RectangleShape object) const
{
	sf::Vector2f position = object.getPosition();
	sf::Vector2f size = object.getSize();

	return sf::FloatRect(position.x, position.y, size.x, size.y);
}
