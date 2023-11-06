#include <random>
#include <chrono>
#include "GameObject.h"
#include "Scene.h"
#include "Components/ObjectName.h"

void EnemySpawn(Scene* scene)
{
	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	std::mt19937 gen(seed);
	std::uniform_int_distribution<int> distribution(1, 4);
	int nombre_aleatoire = distribution(gen);
	Maths::Vector2f spawn_pos(0, 0);

	if (nombre_aleatoire == 1)
	{
		spawn_pos.SetXY(400, -100);
	}
	else if (nombre_aleatoire == 2)
	{
		spawn_pos.SetXY(900, 400);
	}
	else if (nombre_aleatoire == 3)
	{
		spawn_pos.SetXY(400, 900);
	}
	else if (nombre_aleatoire == 4)
	{
		spawn_pos.SetXY(-100, 400);
	}
	ObjectName name = ObjectName::EnemyName;
	int hp = 0;
	int speed = 0;
	int damage = 0;
	if (scene->GetLevel() == 1)
	{
		hp = 30;
		speed = 20;
		damage = 10;
	}
	else if (scene->GetLevel() == 2)
	{
		hp = 30;
		speed = 30;
		damage = 15;
	}
	else if (scene->GetLevel() == 3)
	{
		hp = 60;
		speed = 20;
		damage = 25;
	}

	GameObject* enemy = scene->CreateEnemy(name, spawn_pos, hp, speed, damage);
}

std::chrono::high_resolution_clock::time_point CheckIfIsTimeToEnemySpawn(Scene* scene, std::chrono::high_resolution_clock::time_point time_for_enemy_spawn)
{
	auto duration = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - time_for_enemy_spawn);
	double cooldown = 0;
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
