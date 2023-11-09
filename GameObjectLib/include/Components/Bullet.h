#pragma once

#include "GameObject.h"
#include "SFML/Audio.hpp"

class Bullet : public Component
{
public:
	Bullet();
	~Bullet();

	void SetVectorDirector(Maths::Vector2<float> new_vector_director) { vector_director = new_vector_director; }
	Maths::Vector2f GetVectorDirector() { return vector_director; }

	void SetTower(GameObject* new_tower) { tower = new_tower; }
	GameObject* GetTower() { return tower; }

	void PlaySound();
	void StopSound();
	void Move(std::vector<GameObject*>* gameObjects, float deltaTimeMillisecondes);
	void Update(float deltaTimeMillisecondes, std::vector<GameObject*>* gameObjects) override;
	bool Delete(std::vector<GameObject*>* gameObjects);

private:
	Maths::Vector2f vector_director;
	float deltaTimeMillisecondes;
	float sizeWindow;
	float tailleParDefault = 50;
	sf::SoundBuffer* soundBufferBullet;
	sf::Sound* soundBullet;
	GameObject* tower;
};