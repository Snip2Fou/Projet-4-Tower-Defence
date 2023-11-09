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


std::chrono::high_resolution_clock::time_point EnemySpawn::CheckIfIsTimeToEnemySpawn(Scene* scene, std::chrono::high_resolution_clock::time_point time_for_enemy_spawn)

{
	auto duration = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - time_for_enemy_spawn);
	double cooldown = 1.2;

	


	std::random_device rd;  // Initialise le générateur de nombres aléatoires
	std::mt19937 rng(rd()); // Utilise le générateur mersenne_twister_engine

	// Génère un nombre aléatoire entre 1 et 100
	int randomEnemySpawn = std::uniform_int_distribution<int>(1, 100)(rng);

	if (nbVague != nbVagueMax)
	{
		if (duration.count() >= cooldown && nbEnnemiVague < vaguemaxEnnemi)
		{
			if (randomEnemySpawn <= spawnRateEnnemi1)
			{
				EnemySpawn1(scene);
				nbEnnemiVague++;
			}
			else if (randomEnemySpawn > spawnRateEnnemi1 && randomEnemySpawn <= spawnRateEnnemi1 + spawnRateEnnemi2)
			{
				EnemySpawn2(scene);
				nbEnnemiVague++;
			}
			if (randomEnemySpawn > spawnRateEnnemi1 + spawnRateEnnemi2 && randomEnemySpawn <= spawnRateEnnemi1 + spawnRateEnnemi2 + spawnRateBoss)
			{
				BossSpawn(scene);
				nbEnnemiVague++;
			}

			std::cout << "Ennemis : " << nbEnnemiVague << std::endl;
			std::cout << "Max ennemis : " << vaguemaxEnnemi << std::endl;
			std::cout << "Vagues : " << nbVague << std::endl;


			time_for_enemy_spawn = std::chrono::high_resolution_clock::now();
		}
		else if (nbEnnemiVague >= vaguemaxEnnemi && duration.count() >= cooldownBTWwaves)
		{
			nbEnnemiVague = 0;
			vaguemaxEnnemi = vaguemaxEnnemi * coeffMultiplicateurEnnemi;
			nbVague++;
		}
	}

	return time_for_enemy_spawn;
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

