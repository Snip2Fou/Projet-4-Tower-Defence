#pragma once
#include <vector>

#include "Maths/Vector2.h"
#include "Components/Component.h"
#include "SFML/Graphics.hpp"
#include "Components/ObjectName.h"

class Component;

class GameObject
{
public:
	GameObject() = default;
	virtual ~GameObject() = default;

	ObjectName GetName() const { return name; }
	Maths::Vector2<float> GetPosition() const { return position; }
	sf::FloatRect getBounds(sf::RectangleShape object) const;
	void SetName(const ObjectName& _name) { name = _name; }
	void SetPosition(const Maths::Vector2<float>& _position) { position = _position; }
	void AddComponent(Component* _component);

	template<typename T>
	T* CreateComponent()
	{
		T* component = new T();
		component->SetOwner(this);
		components.push_back(component);
		return component;
	}

	template<typename T>
	T* getComponent()
	{
		for (Component* component : components)
		{
			T* derived = dynamic_cast<T*>(component);
			if (derived)
			{
				return derived;
			}
		}
		return nullptr;
	}

	void RemoveComponent(Component* _component);

	void Update(float deltaTimeMillisecondes, std::vector<GameObject*>* gameObjects) const;

	void Render(sf::RenderWindow* _window) const;

private:
	ObjectName name;
	Maths::Vector2<float> position = Maths::Vector2f::Zero;
	std::vector<Component*> components;
	sf::RectangleShape shape;
};
