#include <iostream>
#include <random>
#include <chrono>
#include "GameObject.h"
#include "Scene.h"
#include "Components/ObjectName.h"
#include "EnemySpawn.h"

void EnemySpawn::EnemySpawn1(Scene* scene)
{
	Maths::Vector2f spawn_pos(0, 0);
	std::cout << "ennemi" << std::endl;

	spawn_pos.SetXY(-50, 400);

	ObjectName name = ObjectName::EnemyName;
	int hp = 30;
	int speed = 20;
	int damage = 10;

	GameObject* enemy = scene->CreateEnemy(name, spawn_pos, hp, speed, damage, "texture_enemy1");
}

void EnemySpawn::EnemySpawn2(Scene* scene)
{
	Maths::Vector2f spawn_pos(0, 0);
	std::cout << "ennemi2" << std::endl;

	spawn_pos.SetXY(-50, 400);

	ObjectName name = ObjectName::EnemyName;
	int hp = 30;
	int speed = 50;
	int damage = 10;

	GameObject* enemy = scene->CreateEnemy(name, spawn_pos, hp, speed, damage, "texture_enemy2");
}

void EnemySpawn::BossSpawn(Scene* scene)
{
	Maths::Vector2f spawn_pos(0, 0);
	std::cout << "boss" << std::endl;

	spawn_pos.SetXY(0, 400);

	ObjectName name = ObjectName::EnemyName;
	int hp = 30;
	int speed = 10;
	int damage = 10;

	GameObject* enemy = scene->CreateEnemy(name, spawn_pos, hp, speed, damage, "texture_boss"); 
}

std::chrono::high_resolution_clock::time_point EnemySpawn::CheckIfIsTimeToEnemySpawn(Scene* scene, std::chrono::high_resolution_clock::time_point time_for_enemy_spawn)
{
	auto duration = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - time_for_enemy_spawn);
	double cooldown = 1.2;

	if (duration.count() >= cooldown)
	{
		EnemySpawn1(scene);
		EnemySpawn2(scene);
		BossSpawn(scene);
		time_for_enemy_spawn = std::chrono::high_resolution_clock::now();
	}
	return time_for_enemy_spawn;
}
