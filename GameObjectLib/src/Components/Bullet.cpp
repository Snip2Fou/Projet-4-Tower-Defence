#include "Components/Bullet.h"
#include <iostream>

#include "Components/SquareCollider.h"
#include "Components/ShapeRenderer.h"
#include "Components/ObjectName.h"
#include "Components/Enemy.h"
#include "Components/Tower.h"

Bullet::Bullet()
{
	soundBufferBullet = new sf::SoundBuffer;
	if (!soundBufferBullet->loadFromFile("Assets/Son/laser-gun-72558.wav")) {
		std::cout << "erreur de chargement du fichier" << std::endl;
	}
	soundBullet = new sf::Sound;
	PlaySound();
}

Bullet::~Bullet()
{
	delete soundBufferBullet;
	delete soundBullet;
	soundBullet = nullptr;
	soundBufferBullet = nullptr;
}

void Bullet::PlaySound()
{
	soundBullet->setBuffer(*soundBufferBullet);
	soundBullet->play();
}

void Bullet::StopSound()
{
	soundBullet->setBuffer(*soundBufferBullet);
	soundBullet->stop();
}


void Bullet::Move(std::vector<GameObject*>* gameObjects, float deltaTimeMillisecondes) {
	for (GameObject* const& gameObject : *gameObjects) {
		bool collision = false;
		if (gameObject->GetName() == ObjectName::EnemyName) {
			collision = GetOwner()->getComponent<SquareCollider>()->IsColliding(*GetOwner()->getComponent<SquareCollider>(), *gameObject->getComponent<SquareCollider>());
			if (collision) {
				gameObject->getComponent<Enemy>()->SetHp(gameObject->getComponent<Enemy>()->GetHp() - tower->getComponent<Tower>()->GetDamage());
			}
		}
	}
	if ((!GetOwner()->getComponent<SquareCollider>()->GetCanMoving()["up"] || !GetOwner()->getComponent<SquareCollider>()->GetCanMoving()["down"] ||
		!GetOwner()->getComponent<SquareCollider>()->GetCanMoving()["left"] || !GetOwner()->getComponent<SquareCollider>()->GetCanMoving()["right"])
		|| (GetOwner()->GetPosition().GetX() > 900 || GetOwner()->GetPosition().GetX() < -100) ||
		(GetOwner()->GetPosition().GetY() > 900 || GetOwner()->GetPosition().GetY() < -100)) {
		Delete(gameObjects);
	}
	else {
		GetOwner()->SetPosition(GetOwner()->GetPosition() + vector_director * deltaTimeMillisecondes);
	}
}

void Bullet::Update(float deltaTimeMillisecondes, std::vector<GameObject*>* gameObjects) {
	Move(gameObjects, deltaTimeMillisecondes);
}

bool Bullet::Delete(std::vector<GameObject*>* gameObjects) {
	GetOwner()->RemoveComponent(GetOwner()->getComponent<Bullet>());
	GetOwner()->RemoveComponent(GetOwner()->getComponent<ShapeRenderer>());
	GetOwner()->RemoveComponent(GetOwner()->getComponent<SquareCollider>());
	for (auto it = gameObjects->begin(); it != gameObjects->end(); ++it)
	{
		if (*it == GetOwner())
		{
			delete GetOwner();
			gameObjects->erase(it);
			return true;
		}
	}
	return false;
}