#pragma once

#include "GameObject.h"
#include "SFML/Audio.hpp"

class Enemy : public Component
{
public:
	Enemy();
	~Enemy() override;

	void SetHp(int new_hp) { hp = new_hp; }
	int GetHp() { return hp; }
	void SetSpeed(int new_speed) { speed = new_speed; }
	int GetSpeed() { return speed; }
	void SetDamage(int new_damage) { damage = new_damage; }
	int GetDamage() { return damage; }
	void PlaySound();
	void StopSound();
	void Move(std::vector<GameObject*>* gameObjects);
	
	bool isDead(std::vector<GameObject*>* gameObjects);
	void ResetScore(int new_score);

	void Update(float deltaTimeMillisecondes, std::vector<GameObject*>* gameObjects) override;

private:
	int hp;
	int speed;
	int damage;
	sf::SoundBuffer* soundBufferEnemy;
	sf::Sound* soundEnemy;
	sf::Clock clock;
	sf::Time attack_cooldown = sf::seconds(0.3);
	sf::Time elapsedTime;
	int score = 0;
	static int enemyKill;
};
