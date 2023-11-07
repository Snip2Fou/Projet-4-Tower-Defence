#pragma once
#include "GameObject.h"

class Tower : public Component
{
private:
	Maths::Vector2<float> position = Maths::Vector2f::Zero;

public:
	Tower();
	~Tower();

	void Update(float deltaTimeMillisecondes, std::vector<GameObject*>* gameObjects) override;
	Maths::Vector2<float> GetPosition() const { return position; }
};