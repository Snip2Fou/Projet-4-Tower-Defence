#include "Components/Tower.h"
#include "GameObject.h"
#include <iostream>
#include "Components/ShapeRenderer.h"
#include "Components/SquareCollider.h"
#include "Components/Bullet.h"
#include "Components/Enemy.h"

void Tower::Update(float deltaTimeMillisecondes, std::vector<GameObject*>* gameObjects) {
	SearchForTarget(gameObjects);
	Attack(gameObjects);
}

void Tower::SearchForTarget(std::vector<GameObject*>* gameObjects) {
	if (target == nullptr) {
		for (GameObject* const& gameObject : *gameObjects)
		{
			if (gameObject->GetName() == ObjectName::EnemyName) {
				float distance = GetOwner()->GetPosition().Distance(gameObject->GetPosition());
				std::cout << distance << std::endl;
				if (distance <= range) {
					SetTarget(gameObject);
					break;
				}
			}
		}
	}
	else {
		float distance = GetOwner()->GetPosition().Distance(target->GetPosition());
		if (distance > range) {
			SetTarget(nullptr);
			SearchForTarget(gameObjects);
		}
	}
}

void Tower::Attack(std::vector<GameObject*>* gameObjects) {
	if (target != nullptr) {
		elapsedTime = clock.getElapsedTime();
		if (elapsedTime >= attack_cooldown) {
			Maths::Vector2f vector_director = target->GetPosition() - GetOwner()->GetPosition();

			GameObject* gameObject = new GameObject();
			gameObject->SetName(ObjectName::BulletName);
			gameObjects->push_back(gameObject);
			gameObject->SetPosition(GetOwner()->GetPosition());

			ShapeRenderer* shapeRenderer = gameObject->CreateComponent<ShapeRenderer>();
			shapeRenderer->SetSize(sf::Vector2f(10, 10));
			shapeRenderer->SetColor(sf::Color::Green);

			SquareCollider* squareCollider = gameObject->CreateComponent<SquareCollider>();
			squareCollider->SetWidth(10);
			squareCollider->SetHeight(10);

			Bullet* bullet = gameObject->CreateComponent<Bullet>();
			bullet->SetVectorDirector(vector_director.Normalize() * 2);
			bullet->SetTower(GetOwner());

			clock.restart();
		}
	}
}