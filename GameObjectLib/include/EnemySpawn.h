#pragma once
class EnemySpawn {
private:
	void EnemySpawn1(Scene* scene);
	void EnemySpawn2(Scene* scene);
	void BossSpawn(Scene* scene);
public:
	std::chrono::high_resolution_clock::time_point CheckIfIsTimeToEnemySpawn(Scene* scene, std::chrono::high_resolution_clock::time_point time_for_enemy_spawn);
};




