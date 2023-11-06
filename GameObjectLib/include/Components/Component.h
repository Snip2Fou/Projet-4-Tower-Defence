#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "GameObject.h"

class GameObject;

class Component
{
public:
	Component() = default;
	Component(GameObject* owner);
	virtual ~Component() = default;

	virtual void Update(float deltaTimeMillisecondes, std::vector<GameObject*>* gameObjects);
  
	virtual void Render(sf::RenderWindow* _window);
	
	GameObject* GetOwner() const { return owner; }
	void SetOwner(GameObject* _owner) { owner = _owner; }
	float GetHeight() const { return height; }
	float GetWidth() const { return width; }
	void SetWidth(const float _width) { width = _width; }
	void SetHeight(const float _height) { height = _height; }

private:
	GameObject* owner = nullptr;
	float width;
	float height;
};
