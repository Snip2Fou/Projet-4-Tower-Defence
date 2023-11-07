#pragma once

#include "GameObject.h"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <unordered_map>


class Player : public Component
{
private:
	int hp = 100;
	sf::SoundBuffer* soundBuffer;
	sf::Sound* sound;
	Maths::Vector2<float> position = Maths::Vector2f::Zero;

public:
	Player();
	~Player();
  
	int GetHp() {return hp;}
	void SetHp(int new_hp);
	void LossHp(int attack);
	void PlaySound();
	void StopSound();
	void Update(float deltaTimeMillisecondes, std::vector<GameObject*>* gameObjects) override;
	bool isDead(std::vector<GameObject*>* gameObjects);
	void Move(Maths::Vector2f new_position, std::string direction , std::vector<GameObject*>* gameObjects);
	Maths::Vector2<float> GetPosition() const { return position; }
};

