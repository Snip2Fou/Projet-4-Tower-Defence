#pragma once
class EnemySpawn {
private:
    int vaguemaxEnnemi = 5; //Ennemi max vague 1
    int nbEnnemiVague = 0;
    int nbVague = 1;
    double coeffMultiplicateurEnnemi = 1.25;
    int nbVagueMax = 30;

    //Nombre à mettre en seconde
    int cooldownBTWwaves = 8;

    // L'addition de tous les taux de d'apparition des ennemis doit être égal à 100!!!
    int spawnRateEnnemi1 = 60;
    int spawnRateEnnemi2 = 30;
    int spawnRateBoss = 10;

    void EnemySpawn1(Scene* scene);
    void EnemySpawn2(Scene* scene);
    void BossSpawn(Scene* scene);

public:
    std::chrono::high_resolution_clock::time_point CheckIfIsTimeToEnemySpawn(Scene* scene, std::chrono::high_resolution_clock::time_point time_for_enemy_spawn);
};

