#pragma once


void EnemySpawn(Scene* scene);


class Vague
{
public:
	std::chrono::high_resolution_clock::time_point CheckIfIsTimeToEnemySpawn(Scene* scene, std::chrono::high_resolution_clock::time_point time_for_enemy_spawn, int* vague);

private:
	int vaguemaxEnnemi = 5;
	int nbEnnemiVague = 0;
	int nbVague = 1;
};




