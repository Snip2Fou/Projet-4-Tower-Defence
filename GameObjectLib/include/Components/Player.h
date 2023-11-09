#pragma once

#include "GameObject.h"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <unordered_map>
#include <iostream>
#include "Tower.h"


class Player : public Component
{
private:
	int hp = 100;
	sf::SoundBuffer* soundBuffer;
	sf::Sound* sound;
	Maths::Vector2<float> position = Maths::Vector2f::Zero;
	GameObject* choosen_spot = nullptr;
	GameObject* choosen_tower = nullptr;
	std::vector<GameObject*> towers;

public:
	Player();
	~Player();
  
	int GetHp() {return hp;}
	void SetHp(int new_hp);

	GameObject* GetChoosenSpot() { return choosen_spot; }
	void SetChoosenSpot(GameObject* new_choosen_spot) { choosen_spot = new_choosen_spot; }
	void SetChoosenSpotToNullPtr() { choosen_spot = nullptr; }

	GameObject* GetChoosenTower() { return choosen_tower; }
	void SetChoosenTower(GameObject* new_choosen_tower) { choosen_tower = new_choosen_tower; }
	void SetChoosenTowerToNullPtr() { choosen_tower = nullptr; }

	void LossHp(int attack);
	void PlaySound();
	void StopSound();
	void Update(float deltaTimeMillisecondes, std::vector<GameObject*>* gameObjects) override;
	bool isDead(std::vector<GameObject*>* gameObjects);
	void Move(Maths::Vector2f new_position, std::string direction , std::vector<GameObject*>* gameObjects);
	Maths::Vector2<float> GetPosition() const { return position; }

	void CheckBuildTower(std::vector<GameObject*>* gameObjects);
};

