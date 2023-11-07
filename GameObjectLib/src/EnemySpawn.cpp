#include <iostream>
#include <random>
#include <chrono>
#include "GameObject.h"
#include "Scene.h"
#include "Components/ObjectName.h"

void EnemySpawn(Scene* scene)
{
	Maths::Vector2f spawn_pos(0, 0);
	std::cout << "ennemi" << std::endl;

	spawn_pos.SetXY(-50, 400);

	ObjectName name = ObjectName::EnemyName;
	int hp = 30;
	int speed = 20;
	int damage = 10;

	GameObject* enemy = scene->CreateEnemy(name, spawn_pos, hp, speed, damage);
}

std::chrono::high_resolution_clock::time_point CheckIfIsTimeToEnemySpawn(Scene* scene, std::chrono::high_resolution_clock::time_point time_for_enemy_spawn)
{
	auto duration = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - time_for_enemy_spawn);
	double cooldown = 0.5;
	if (scene->GetLevel() == 1)
	{
		cooldown = 1;
	}
	else if (scene->GetLevel() == 2)
	{
		cooldown = 0.85;
	}
	else if (scene->GetLevel() == 3)
	{
		cooldown = 0.7;
	}

	if (duration.count() >= cooldown)
	{
		EnemySpawn(scene);
		time_for_enemy_spawn = std::chrono::high_resolution_clock::now();
	}
	return time_for_enemy_spawn;
}
