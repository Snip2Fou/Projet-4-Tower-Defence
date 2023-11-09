#pragma once
#include "TowerType.h"
#include "GameObject.h"

class Tower : public Component
{
public:
	void SetType(TowerType new_type) { type = new_type; }
	void SetDamage(int new_damage) { damage = new_damage; }
	void SetRange(int new_range) { range = new_range; }
	void SetTarget(GameObject* new_target) { target = new_target; }
	void SetCooldown(sf::Time new_cooldown) { attack_cooldown = new_cooldown; }

	TowerType GetType() { return type; }
	int GetDamage() { return damage; }
	int GetRange() { return range; }
	GameObject* GetTarget() { return target; }

	void Update(float deltaTimeMillisecondes, std::vector<GameObject*>* gameObjects) override;
	void SearchForTarget(std::vector<GameObject*>* gameObjects);
	void Attack(std::vector<GameObject*>* gameObjects);

private:
	TowerType type;
	int damage;
	int range;
	GameObject* target = nullptr;
	sf::Clock clock;
	sf::Time attack_cooldown;
	sf::Time elapsedTime;
};