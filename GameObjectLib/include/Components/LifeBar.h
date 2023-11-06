#pragma once

#include "Component.h"


class LifeBar : public Component
{
public:
	LifeBar() = default;
	~LifeBar() = default;

	void SetHpMax(int new_hp_max) { hp_max = new_hp_max; }
	void SetHp(int new_hp) { hp = new_hp; }

	int GetHpMax() { return hp_max; }
	int GetHp() { return hp; }

	void Update(float deltaTimeMillisecondes, std::vector<GameObject*>* gameObjects) override;

private:
	int hp_max;
	int hp;

};
