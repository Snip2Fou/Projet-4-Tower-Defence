#pragma once

#include "GameObject.h"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <unordered_map>
#include "Ressources.h"

class Player : public Component
{
private:
	int hp = 100;
	sf::SoundBuffer* soundBuffer;
	sf::Sound* sound;
	Maths::Vector2<float> position = Maths::Vector2f::Zero;
	GameObject* ressource1 = nullptr;
	GameObject* ressource2 = nullptr;


public:
	Player();
	~Player();

	int GetHp() { return hp; }
	void SetHp(int new_hp);
	void LossHp(int attack);
	void PlaySound();
	void StopSound();
	void Update(float deltaTimeMillisecondes, std::vector<GameObject*>* gameObjects) override;
	bool isDead(std::vector<GameObject*>* gameObjects);
	Maths::Vector2<float> GetPosition() const { return position; }
	GameObject* GetRessource1() { return ressource1; }
	GameObject* GetRessource2() { return ressource2; }
	void SetRessources1(GameObject* new_ressources) { ressource1 = new_ressources; }
	void SetRessources2(GameObject* new_ressources) { ressource2 = new_ressources; }
};

