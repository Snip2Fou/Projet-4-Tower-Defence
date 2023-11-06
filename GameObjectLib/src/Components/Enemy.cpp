#include "Components/Enemy.h"
#include <iostream>
#include <cmath>
#include "Components/SquareCollider.h"
#include "Components/ObjectName.h"
#include "Components/Player.h"
#include "Components/SpriteRenderer.h"
#include "GameObject.h"

int Enemy::enemyKill = 0;

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
	Maths::Vector2f move_vector(0, 0);
	GameObject* gameobjectplayer = nullptr;
	GetOwner()->getComponent<SquareCollider>()->SetCanMoving("up", true);
	GetOwner()->getComponent<SquareCollider>()->SetCanMoving("down", true);
	GetOwner()->getComponent<SquareCollider>()->SetCanMoving("left", true);
	GetOwner()->getComponent<SquareCollider>()->SetCanMoving("right", true);
	for (GameObject* const& gameObject : *gameObjects) {
		bool collision = false;
		if (GetOwner() != gameObject && gameObject->GetName() != ObjectName::ButtonName) {
			collision = GetOwner()->getComponent<SquareCollider>()->IsColliding(*GetOwner()->getComponent<SquareCollider>(), *gameObject->getComponent<SquareCollider>());
		}
		if (gameObject->GetName() == ObjectName::PlayerName) {

			move_vector.SetXY(gameObject->GetPosition() - GetOwner()->GetPosition());

			gameobjectplayer = gameObject;
			elapsedTime = clock.getElapsedTime();
			if (collision && elapsedTime >= attack_cooldown) {
				gameobjectplayer->getComponent<Player>()->SetHp(gameobjectplayer->getComponent<Player>()->GetHp() - GetDamage());
				clock.restart();
			}
		}
	}
	if (gameobjectplayer) {
		
		move_vector.SetXY(gameobjectplayer->GetPosition() - GetOwner()->GetPosition());

		move_vector = move_vector.Normalize();

		move_vector *= speed / 10;

		if (move_vector.GetY() < 0 && move_vector.GetX() < 0 && 
			GetOwner()->getComponent<SquareCollider>()->GetCanMoving()["up"] && GetOwner()->getComponent<SquareCollider>()->GetCanMoving()["left"]){
			GetOwner()->SetPosition(GetOwner()->GetPosition() + move_vector);
		}
		else if (move_vector.GetY() < 0 && move_vector.GetX() >= 0 &&
			GetOwner()->getComponent<SquareCollider>()->GetCanMoving()["up"] && GetOwner()->getComponent<SquareCollider>()->GetCanMoving()["right"]) {
			GetOwner()->SetPosition(GetOwner()->GetPosition() + move_vector);
		}
		else if (move_vector.GetY() >= 0 && move_vector.GetX() < 0 &&
			GetOwner()->getComponent<SquareCollider>()->GetCanMoving()["down"] && GetOwner()->getComponent<SquareCollider>()->GetCanMoving()["left"]) {
			GetOwner()->SetPosition(GetOwner()->GetPosition() + move_vector);
		}
		else if (move_vector.GetY() >= 0 && move_vector.GetX() >= 0 &&
			GetOwner()->getComponent<SquareCollider>()->GetCanMoving()["down"] && GetOwner()->getComponent<SquareCollider>()->GetCanMoving()["right"]) {
			GetOwner()->SetPosition(GetOwner()->GetPosition() + move_vector);
		}
		else {
			double x = std::abs(move_vector.GetX());
			double y = std::abs(move_vector.GetY());
			if (move_vector.GetY() < 0 && move_vector.GetX() < 0) {
				if (!GetOwner()->getComponent<SquareCollider>()->GetCanMoving()["up"] && !GetOwner()->getComponent<SquareCollider>()->GetCanMoving()["left"]) {
					if (x >= y) {
						if (GetOwner()->getComponent<SquareCollider>()->GetCanMoving()["right"]) {
							move_vector.SetXY(1, 0);
						}
						else if (GetOwner()->getComponent<SquareCollider>()->GetCanMoving()["down"]) {
							move_vector.SetXY(0, 1);
						}
						else {
							move_vector.SetXY(0, 0);
						}
					}
					else {
						if (GetOwner()->getComponent<SquareCollider>()->GetCanMoving()["down"]) {
							move_vector.SetXY(0, 1);
						}
						else if (GetOwner()->getComponent<SquareCollider>()->GetCanMoving()["right"]) {
							move_vector.SetXY(1, 0);
						}
						else {
							move_vector.SetXY(0, 0);
						}
					}
				}
				else if (GetOwner()->getComponent<SquareCollider>()->GetCanMoving()["up"]) {
					move_vector.SetXY(0, -1);
				}
				else if (GetOwner()->getComponent<SquareCollider>()->GetCanMoving()["left"]) {
					move_vector.SetXY(-1, 0);
				}
				else {
					move_vector.SetXY(0, 0);
				}
			}else if (move_vector.GetY() < 0 && move_vector.GetX() >= 0) {
				if (!GetOwner()->getComponent<SquareCollider>()->GetCanMoving()["up"] && !GetOwner()->getComponent<SquareCollider>()->GetCanMoving()["right"]) {
					if (x >= y) {
						if (GetOwner()->getComponent<SquareCollider>()->GetCanMoving()["left"]) {
							move_vector.SetXY(-1, 0);
						}
						else if (GetOwner()->getComponent<SquareCollider>()->GetCanMoving()["down"]) {
							move_vector.SetXY(0, 1);
						}
						else {
							move_vector.SetXY(0, 0);
						}
					}
					else {
						if (GetOwner()->getComponent<SquareCollider>()->GetCanMoving()["down"]) {
							move_vector.SetXY(0, 1);
						}
						else if (GetOwner()->getComponent<SquareCollider>()->GetCanMoving()["left"]) {
							move_vector.SetXY(-1, 0);
						}
						else {
							move_vector.SetXY(0, 0);
						}
					}
				}
				else if (GetOwner()->getComponent<SquareCollider>()->GetCanMoving()["up"]) {
					move_vector.SetXY(0, -1);
				}
				else if (GetOwner()->getComponent<SquareCollider>()->GetCanMoving()["right"]) {
					move_vector.SetXY(1, 0);
				}
				else {
					move_vector.SetXY(0, 0);
				}
			}
			else if (move_vector.GetY() >= 0 && move_vector.GetX() < 0) {
				if (!GetOwner()->getComponent<SquareCollider>()->GetCanMoving()["down"] && !GetOwner()->getComponent<SquareCollider>()->GetCanMoving()["left"]) {
					if (x >= y) {
						if (GetOwner()->getComponent<SquareCollider>()->GetCanMoving()["right"]) {
							move_vector.SetXY(1, 0);
						}
						else if (GetOwner()->getComponent<SquareCollider>()->GetCanMoving()["up"]) {
							move_vector.SetXY(0, -1);
						}
						else {
							move_vector.SetXY(0, 0);
						}
					}
					else {
						if (GetOwner()->getComponent<SquareCollider>()->GetCanMoving()["up"]) {
							move_vector.SetXY(0, -1);
						}
						else if (GetOwner()->getComponent<SquareCollider>()->GetCanMoving()["right"]) {
							move_vector.SetXY(1, 0);
						}
						else {
							move_vector.SetXY(0, 0);
						}
					}
				}
				else if (GetOwner()->getComponent<SquareCollider>()->GetCanMoving()["down"]) {
					move_vector.SetXY(0, 1);
				}
				else if (GetOwner()->getComponent<SquareCollider>()->GetCanMoving()["left"]) {
					move_vector.SetXY(-1, 0);
				}
				else {
					move_vector.SetXY(0, 0);
				}
			}else if (move_vector.GetY() >= 0 && move_vector.GetX() >= 0) {
				if (!GetOwner()->getComponent<SquareCollider>()->GetCanMoving()["down"] && !GetOwner()->getComponent<SquareCollider>()->GetCanMoving()["right"]) {
					if (x >= y) {
						if (GetOwner()->getComponent<SquareCollider>()->GetCanMoving()["left"]) {
							move_vector.SetXY(-1, 0);
						}
						else if (GetOwner()->getComponent<SquareCollider>()->GetCanMoving()["up"]) {
							move_vector.SetXY(0, -1);
						}
						else {
							move_vector.SetXY(0, 0);
						}
					}
					else {
						if (GetOwner()->getComponent<SquareCollider>()->GetCanMoving()["up"]) {
							move_vector.SetXY(0, -1);
						}
						else if (GetOwner()->getComponent<SquareCollider>()->GetCanMoving()["left"]) {
							move_vector.SetXY(-1, 0);
						}
						else {
							move_vector.SetXY(0, 0);
						}
					}
				}
				else if (GetOwner()->getComponent<SquareCollider>()->GetCanMoving()["down"]) {
					move_vector.SetXY(0, 1);
				}
				else if (GetOwner()->getComponent<SquareCollider>()->GetCanMoving()["left"]) {
					move_vector.SetXY(-1, 0);
				}
				else {
					move_vector.SetXY(0, 0);
				}
			}
			else {
				move_vector.SetXY(0, 0);
			}

			move_vector = move_vector.Normalize();

			move_vector *= speed / 10;
			GetOwner()->SetPosition(GetOwner()->GetPosition() + move_vector);
			
		}
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





void Enemy::ResetScore(int new_score)
{
	enemyKill = new_score; 
}

bool Enemy::isDead(std::vector<GameObject*>* gameObjects)
{
	if (hp <= 0)
	{

	  GetOwner()->RemoveComponent(GetOwner()->getComponent<Enemy>());
		GetOwner()->RemoveComponent(GetOwner()->getComponent<SpriteRenderer>());
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
	}
	else
	{
		return false;
	}
}


void Enemy::Update(float deltaTimeMillisecondes, std::vector<GameObject*>* gameObjects) {
	Move(gameObjects);
	isDead(gameObjects);
}

