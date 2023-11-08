#include <iostream>
#include <random>
#include <chrono>
#include "GameObject.h"
#include "Scene.h"
#include "EnemySpawn.h"
#include "Components/ObjectName.h"
#include "Components/Player.h"


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


std::chrono::high_resolution_clock::time_point Vague::CheckIfIsTimeToEnemySpawn(Scene* scene, std::chrono::high_resolution_clock::time_point time_for_enemy_spawn, int *vague)

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





	if (duration.count() >= cooldown && nbEnnemiVague < vaguemaxEnnemi)
	{

		nbEnnemiVague++;
		std::cout << nbEnnemiVague << std::endl;
		std::cout << vaguemaxEnnemi << std::endl;
		std::cout << nbVague << std::endl;

		EnemySpawn(scene);

		EnemySpawn1(scene);
		EnemySpawn2(scene);
		BossSpawn(scene);

		time_for_enemy_spawn = std::chrono::high_resolution_clock::now();
		
	}
	else if(nbEnnemiVague >= vaguemaxEnnemi)
	{
		nbEnnemiVague = 0;
		vaguemaxEnnemi = vaguemaxEnnemi*1.25;
		nbVague++;

	}


	/*if (*vague == 1)
	{
		if (duration.count() >= cooldown && nbEnnemiVague1 <= vague1maxEnnemi)
			{
				nbEnnemiVague1++;
				std::cout << nbEnnemiVague1 << std::endl;
				EnemySpawn(scene);
				time_for_enemy_spawn = std::chrono::high_resolution_clock::now();
			}
		else
		{
			vague++;
		}
	}

	if (*vague == 2)
	{
		if (duration.count() >= cooldown && nbEnnemiVague1 == vague1maxEnnemi  && nbEnnemiVague2 <= vague2maxEnnemi)
		{
			nbEnnemiVague2++;
			std::cout << nbEnnemiVague2 << std::endl;
			EnemySpawn(scene);
			time_for_enemy_spawn = std::chrono::high_resolution_clock::now();
		}
		else
		{
			vague++;
		}
	}


	if (*vague == 3)
	{
		if (duration.count() >= cooldown && nbEnnemiVague2 == vague2maxEnnemi && nbEnnemiVague3 <= vague3maxEnnemi)
		{
			nbEnnemiVague3++;
			std::cout << nbEnnemiVague3 << std::endl;
			EnemySpawn(scene);
			time_for_enemy_spawn = std::chrono::high_resolution_clock::now();
		}
		else
		{
			vague++;
		}
	}*/
	return time_for_enemy_spawn;
}
