#pragma once
class EnemySpawn {
private:
    int vaguemaxEnnemi = 7; //Ennemi max vague 1
    int nbEnnemiVague = 0;
    double coeffMultiplicateurEnnemi = 1.25;
    int nbVague = 1;
    int nbVagueMax = 30;
    bool verifVagueBoss;

    //Nombre à mettre en seconde
    double cooldownBTWwaves = 8;
    double cooldown = 1.2;

    // L'addition de tous les taux de d'apparition des ennemis doit être égal à 100!!!
    int spawnRateEnnemi1 = 70;
    int spawnRateEnnemi2 = 30;
    

    void EnemySpawn1(Scene* scene);
    void EnemySpawn2(Scene* scene);
    void BossSpawn(Scene* scene);

public:
    std::chrono::high_resolution_clock::time_point CheckIfIsTimeToEnemySpawn(Scene* scene, std::chrono::high_resolution_clock::time_point time_for_enemy_spawn);
};



class Vague {
private:
    int nbVagueDebut; // Numéro de la première vague concernée
    int nbVagueFin;   // Numéro de la dernière vague concernée
    int newVaguemaxEnnemi;
    double newCooldown;
    double newCooldownBTWwaves;
    

public:
    Vague(int debut, int fin, int newMax, double newCooldownEnnemi, double newCooldownWaves) : nbVagueDebut(debut), nbVagueFin(fin), newVaguemaxEnnemi(newMax), newCooldown(newCooldownEnnemi), newCooldownBTWwaves(newCooldownWaves) {}

    void AppliquerVague(int& vaguemaxEnnemi,double& cooldown, double& cooldownBTWwaves, int nbVague) {
        if (nbVague >= nbVagueDebut && nbVague <= nbVagueFin) {
            vaguemaxEnnemi = newVaguemaxEnnemi;
            cooldown = newCooldown;
            cooldownBTWwaves = newCooldownBTWwaves;
        }
    }
};