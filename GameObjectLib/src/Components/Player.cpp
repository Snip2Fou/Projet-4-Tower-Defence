#include "Components/Player.h"
#include "GameObject.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Components/SpriteRenderer.h"
#include "Components/SquareCollider.h"
#include <Components/Enemy.h>
#include "Components/ObjectName.h"
#include "Components/LifeBar.h"
#include "Components/LifeBarRenderer.h"
#include <cmath>


Player::Player()
{
	soundBuffer = new sf::SoundBuffer;
	if (!soundBuffer->loadFromFile("Assets/Son/concrete-footsteps-6752.wav")) {
		std::cout << "erreur de chargement du fichier" << std::endl;
	}
	sound = new sf::Sound;
}

Player::~Player()
{
	delete soundBuffer;
	delete sound;
	sound = nullptr;
	soundBuffer = nullptr;
}

void Player::SetHp(int new_hp) 
{
	hp = new_hp;
}


void Player::LossHp(int attack)
{
	hp -= attack;
}

bool Player::isDead(std::vector<GameObject*>* gameObjects)
{
	if (hp <= 0)
	{
		std::cout << "T'es mort!!" << std::endl;
		GetOwner()->RemoveComponent(GetOwner()->getComponent<Player>());
		GetOwner()->RemoveComponent(GetOwner()->getComponent<SpriteRenderer>());
		GetOwner()->RemoveComponent(GetOwner()->getComponent<SquareCollider>());
		GetOwner()->RemoveComponent(GetOwner()->getComponent<LifeBar>());
		GetOwner()->RemoveComponent(GetOwner()->getComponent<LifeBarRenderer>());
		for (auto it = gameObjects->begin(); it != gameObjects->end(); ++it)
		{
			if (*it == GetOwner())
			{
				delete GetOwner();
				gameObjects->erase(it);
				return true;
			}
		}
	}
	else
	{
		return false;
	}
}

void Player::SetAngle(sf::RenderWindow* window)
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
	Maths::Vector2f mousePositionVec(mousePosition.x, mousePosition.y);
	Maths::Vector2f VectorPlayerMouse = mousePositionVec - GetOwner()->GetPosition();


	float angleRadians = std::atan2(VectorPlayerMouse.y, VectorPlayerMouse.x);
	float angle = angleRadians * 180.0f / M_PI;
	if (angle < 0)
	{
		angle += 360.0f;
	}

	Angle=angle;
}


void Player::PlaySound()
{
	sound->setBuffer(*soundBuffer);
	sound->play();
}

void Player::StopSound()
{
	sound->setBuffer(*soundBuffer);
	sound->stop();
}

void Player::Update(float deltaTimeMillisecondes, std::vector<GameObject*>* gameObjects) {

	GetOwner()->getComponent<SpriteRenderer>()->GetSprite()->setRotation(GetAngle()+90);
};

void Player::Move(Maths::Vector2f new_position, std::string direction, std::vector<GameObject*>* gameObjects) {
	GetOwner()->getComponent<SquareCollider>()->SetCanMoving("up", true);
	GetOwner()->getComponent<SquareCollider>()->SetCanMoving("down", true);
	GetOwner()->getComponent<SquareCollider>()->SetCanMoving("left", true);
	GetOwner()->getComponent<SquareCollider>()->SetCanMoving("right", true);
	for (GameObject* const& gameObject : *gameObjects)
	{
		if (gameObject->GetName() != ObjectName::PlayerName && gameObject->GetName() != ObjectName::ButtonName) {
			GetOwner()->getComponent<SquareCollider>()->IsColliding(*GetOwner()->getComponent<SquareCollider>(), *gameObject->getComponent<SquareCollider>());
		}
	}
	if (direction == "up" && GetOwner()->getComponent<SquareCollider>()->GetCanMoving()["up"]) {
		GetOwner()->SetPosition(new_position);
	}else if (direction == "down" && GetOwner()->getComponent<SquareCollider>()->GetCanMoving()["down"]) {
		GetOwner()->SetPosition(new_position);
	}else if (direction == "left" && GetOwner()->getComponent<SquareCollider>()->GetCanMoving()["left"]) {
		GetOwner()->SetPosition(new_position);
	}else if (direction == "right" && GetOwner()->getComponent<SquareCollider>()->GetCanMoving()["right"]) {
		GetOwner()->SetPosition(new_position);
	}
}

