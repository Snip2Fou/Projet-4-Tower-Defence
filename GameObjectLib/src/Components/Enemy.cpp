#include "Components/Enemy.h"
#include <iostream>
#include <cmath>
#include "Components/SquareCollider.h"
#include "Components/ObjectName.h"
#include "Components/Player.h"
#include "Components/SpriteRenderer.h"
#include "GameObject.h"


Enemy::Enemy()
{
	soundBufferEnemy = new sf::SoundBuffer;
	if (!soundBufferEnemy->loadFromFile("Assets/Son/warning-75933.wav")) {
		std::cout << "erreur de chargement du fichier" << std::endl;
	}
	soundEnemy = new sf::Sound;
	//PlaySound();
}

Enemy::~Enemy()
{
	delete soundBufferEnemy;
	delete soundEnemy;
	soundEnemy = nullptr;
	soundBufferEnemy = nullptr;
}

void Enemy::Move(std::vector<GameObject*>* gameObjects) {

	if (GetOwner()->GetPosition().GetX() < 200) {
		Maths::Vector2f move_vector(1, 0);
		move_vector = move_vector.Normalize();
		move_vector *= speed / 10;
		GetOwner()->SetPosition(GetOwner()->GetPosition() + move_vector);
	}
	else if (GetOwner()->GetPosition().GetX() >= 200 && GetOwner()->GetPosition().GetX() <= 220 && GetOwner()->GetPosition().GetY() > 80) {
		Maths::Vector2f move_vector(0, -1);
		move_vector = move_vector.Normalize();
		move_vector *= speed / 10;
		GetOwner()->SetPosition(GetOwner()->GetPosition() + move_vector);
	}
	else if (GetOwner()->GetPosition().GetY() <= 80 && GetOwner()->GetPosition().GetY() <= 100 && GetOwner()->GetPosition().GetX() < 500) {
		Maths::Vector2f move_vector(1, 0);
		move_vector = move_vector.Normalize();
		move_vector *= speed / 10;
		GetOwner()->SetPosition(GetOwner()->GetPosition() + move_vector);
	}
	else if (GetOwner()->GetPosition().GetX() >= 500 && GetOwner()->GetPosition().GetX() <= 520 && GetOwner()->GetPosition().GetY() < 650) {
		Maths::Vector2f move_vector(0, 1);
		move_vector = move_vector.Normalize();
		move_vector *= speed / 10;
		GetOwner()->SetPosition(GetOwner()->GetPosition() + move_vector);
	}
	else if (GetOwner()->GetPosition().GetY() >= 650 && GetOwner()->GetPosition().GetY() <= 670 && GetOwner()->GetPosition().GetX() < 900) {
		Maths::Vector2f move_vector(1, 0);
		move_vector = move_vector.Normalize();
		move_vector *= speed / 10;
		GetOwner()->SetPosition(GetOwner()->GetPosition() + move_vector);
	}
	}

void Enemy::PlaySound()
{
	soundEnemy->setBuffer(*soundBufferEnemy);
	soundEnemy->play();
}

void Enemy::StopSound()
{
	soundEnemy->setBuffer(*soundBufferEnemy);
	soundEnemy->stop();
}

bool Enemy::isDead(std::vector<GameObject*>* gameObjects)
{
	if (hp <= 0)
	{
		Delete(gameObjects);
		return true;
	}
	else
	{
		return false;
	}
}


void Enemy::Update(float deltaTimeMillisecondes, std::vector<GameObject*>* gameObjects) {
	Move(gameObjects);
	std::vector<GameObject*> gameObjects2 = *gameObjects;
	if (GetOwner()->GetPosition().GetX() > 800) {
		for (int i = 0; i < gameObjects2.size(); i++) {
			if (gameObjects2[i]->GetName() == ObjectName::PlayerName) {
				gameObjects2[i]->getComponent<Player>()->SetHp(gameObjects2[i]->getComponent<Player>()->GetHp() - GetDamage());
				std::cout << gameObjects2[i]->getComponent<Player>()->GetHp() << std::endl;
				break;
			}
		}
		Delete(gameObjects);
	}
	else {
		isDead(gameObjects);
	}
}

void Enemy::Delete(std::vector<GameObject*>* gameObjects) {
	GetOwner()->RemoveComponent(GetOwner()->getComponent<Enemy>());
	GetOwner()->RemoveComponent(GetOwner()->getComponent<SpriteRenderer>());
	GetOwner()->RemoveComponent(GetOwner()->getComponent<SquareCollider>());
	for (auto it = gameObjects->begin(); it != gameObjects->end(); ++it)
	{
		if (*it == GetOwner())
		{
			delete GetOwner();
			gameObjects->erase(it);
			break;
		}
	}
}

