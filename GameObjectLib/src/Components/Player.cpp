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

int Player::GetHp(){
	std::string line;
	std::string data;
	std::ifstream myfile("Model.txt");
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			size_t pos = line.find("Life");
			if (pos != std::string::npos) {
				std::string data = line.substr(pos + 5);
				std::cout << "Data after Life: " << data << std::endl;
			}
		}
		myfile.close();
	}
	else {
		std::cout << "Unable to open file" << std::endl;
	}
	return std::stoi(data);
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

};

