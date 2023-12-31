#include "Components/Player.h"
#include "GameObject.h"
#include <fstream>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Components/SpriteRenderer.h"
#include "Components/SquareCollider.h"
#include <Components/Enemy.h>
#include "Components/ObjectName.h"
#include "Components/LifeBar.h"
#include "Components/LifeBarRenderer.h"
#include <cmath>
#include "Components/Ressources.h"
#include "Components/Tower.h"
#include "Components/TowerType.h"
#include "Components/Button.h"
#include "Components/ShapeRenderer.h"


Player::Player()
{
	soundBuffer = new sf::SoundBuffer;
	if (!soundBuffer->loadFromFile("Assets/Son/concrete-footsteps-6752.wav")) {
		std::cout << "erreur de chargement du fichier" << std::endl;
	}
	sound = new sf::Sound;
	std::string line;
	std::string data = "";
	int dataInt = 0;
	std::ifstream myfile("Model.txt");
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			size_t pos = line.find("Life");
			if (pos != std::string::npos) {
				std::string data = line.substr(pos + 5);
				dataInt = stoi(data);
			}
		}
		myfile.close();
	}
	else {
		std::cout << "Unable to open file" << std::endl;
	}
	hp = dataInt;
}

Player::~Player()
{
	delete soundBuffer;
	delete sound;
	delete ressource1;
	delete ressource2;
	ressource1 = nullptr;
	ressource2 = nullptr;
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
	CheckBuildTower(gameObjects);
};

void Player::CheckBuildTower(std::vector<GameObject*>* gameObjects) {
	if (choosen_spot != nullptr && choosen_tower != nullptr ) {
		if ((choosen_tower->getComponent<Button>()->type == "ButtonTower1" && ressource1->getComponent<Ressources>()->GetNombre() >= 1200)
			|| (choosen_tower->getComponent<Button>()->type == "ButtonTower2" && ressource1->getComponent<Ressources>()->GetNombre() >= 3000)
			|| (choosen_tower->getComponent<Button>()->type == "ButtonTower3" && ressource1->getComponent<Ressources>()->GetNombre() >= 5000)) {
			auto gameObject = new GameObject();
			gameObject->SetName(ObjectName::TowerName);
			gameObject->SetPosition(choosen_spot->GetPosition());
			gameObjects->push_back(gameObject);

			Tower* tower = gameObject->CreateComponent<Tower>();
			if (choosen_tower->getComponent<Button>()->type == "ButtonTower1") {
				tower->SetType(TowerType::ArcherType);
				tower->SetDamage(5);
				tower->SetRange(150);
				tower->SetCooldown(sf::seconds(0.5));
				ressource1->getComponent<Ressources>()->SetNombre(-1200);
			}
			else if (choosen_tower->getComponent<Button>()->type == "ButtonTower2") {
				tower->SetType(TowerType::MageType);
				tower->SetDamage(10);
				tower->SetRange(125);
				tower->SetCooldown(sf::seconds(0.75));
				ressource1->getComponent<Ressources>()->SetNombre(-3000);
			}
			else if (choosen_tower->getComponent<Button>()->type == "ButtonTower3") {
				tower->SetType(TowerType::BomberType);
				tower->SetDamage(15);
				tower->SetRange(100);
				tower->SetCooldown(sf::seconds(1));
				ressource1->getComponent<Ressources>()->SetNombre(-5000);
			}

			ShapeRenderer* shape_renderer = gameObject->CreateComponent<ShapeRenderer>();
			shape_renderer->SetSize(choosen_spot->getComponent<Button>()->Size);

			towers.push_back(gameObject);
			choosen_tower->getComponent<Button>()->is_selected = false;
			choosen_tower->getComponent<Button>()->color = choosen_tower->getComponent<Button>()->colorNothing;
			choosen_tower->getComponent<ShapeRenderer>()->SetColor(choosen_tower->getComponent<Button>()->color);
			choosen_spot->getComponent<Button>()->is_selected = false;
			choosen_spot->getComponent<Button>()->is_activate = false;
			choosen_spot->getComponent<Button>()->color = choosen_tower->getComponent<Button>()->colorNothing;
			choosen_spot->getComponent<ShapeRenderer>()->SetColor(choosen_spot->getComponent<Button>()->color);
			choosen_spot->getComponent<Button>()->target = gameObject;
			choosen_spot = nullptr;
			choosen_tower = nullptr;
		}
	}
}
