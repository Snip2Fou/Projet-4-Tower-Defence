#pragma once
#include "TowerType.h"
#include "Enemy.h"
#include "GameObject.h"

class Tower : public Component
{
public:
	void SetType(TowerType new_type) { type = new_type; }

	TowerType GetType() { return type; }

private:
	TowerType type;
	int damage;
	int range;
	Enemy target;
};