#include "Components/Tower.h"
#include "GameObject.h"
#include <iostream>

void Tower::Update(float deltaTimeMillisecondes, std::vector<GameObject*>* gameObjects) {
	SearchForTarget(gameObjects);
}

void Tower::SearchForTarget(std::vector<GameObject*>* gameObjects) {
	if (target == nullptr) {
		std::cout << "eeee" << std::endl;
		for (GameObject* const& gameObject : *gameObjects)
		{
			if (gameObject->GetName() == ObjectName::EnemyName) {
				float distance = GetOwner()->GetPosition().Distance(gameObject->GetPosition());
				std::cout << distance << std::endl;
				if (distance >= range) {
					SetTarget(gameObject);
					break;
					std::cout << "rrr " << std::endl;
				}
			}
		}
	}
}
