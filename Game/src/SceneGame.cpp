#include <chrono>

#include "eventGame.h"
#include "eventPause.h"
#include "Scenes.h"
#include "Game.h"
#include "EnemySpawn.h"
#include "TowerSpot.h"
#include "Button.h"

int SceneGame::LoopGame(sf::RenderWindow* window, bool pause)
{
	Game game;
	Scene scene;
	EventFunctionsGame eventFunction;
	EventFunctionPause eventFunctionPause;
	EnemySpawn enemySpawn;


	// Bouton Pause
	Button buttonClass;
	GameObject* buttonPause = buttonClass.createButtonObj(&scene, "Pause");
	if (buttonPause == nullptr) {
		return 1;
	}
	eventFunction.buttonList.push_back(buttonPause);

	scene.SetTexture("texture_floor", "Assets/Image/floor-1.png");
	scene.SetTexture("texture_enemy1", "Assets/Image/zombie.png");
	scene.SetTexture("texture_enemy2", "Assets/Image/GreenGrougrou.png");
	scene.SetTexture("texture_life_bar", "Assets/Image/life_bar.png");
	scene.SetTexture("texture_boss", "Assets/Image/thomasBoss.png");

	GameObject* player = scene.CreatePlayer(ObjectName::PlayerName, Maths::Vector2f(375, 5), 200);

	sf::Clock clock;
	auto time_for_enemy_spawn = std::chrono::high_resolution_clock::now();

	sf::Texture background = scene.GetTetxure()["texture_floor"];

	// Créer un sprite avec la texture chargée
	sf::Sprite sprite(background);

	TowerSpot spotClass;

	GameObject* button1 = spotClass.createButtonObj(&scene, "1");
	GameObject* button2 = spotClass.createButtonObj(&scene, "2");
	GameObject* button3 = spotClass.createButtonObj(&scene, "3");

	clock.restart();

	bool sceneOn = true;
	bool pauseOn = false;
	while (sceneOn)
	{
		if (player->getComponent<Player>()->isDead(scene.GetGameObjects()))
		{
			return 0;
		}
		// Récupérer la taille de la fenêtre
		sf::Vector2u windowSize = window->getSize();

		// Redimensionner le sprite pour qu'il remplisse la fenêtre
		sprite.setScale((float)windowSize.x / sprite.getTexture()->getSize().x, (float)windowSize.y / sprite.getTexture()->getSize().y);

		sf::Time deltaTime = clock.restart();
		float deltaTimeMilliseconds = deltaTime.asMilliseconds();

		if (pauseOn == false)
		{
			sceneOn = eventFunction.loopEvent(player, 50, window, game.HorizontalOrigin, game.VerticalOrigin, &scene, deltaTimeMilliseconds, &pauseOn); //Enlever pour pause


			time_for_enemy_spawn = enemySpawn.CheckIfIsTimeToEnemySpawn(&scene, time_for_enemy_spawn); //Enlever pour pause

			scene.Update(deltaTimeMilliseconds); //Enlever pour pause
		}
		if (pauseOn)
		{
			int temp = eventFunctionPause.loopEvent(window, &pauseOn);
			if (temp == 1)
			{
				window->close();
				return -1;
			}
		}
		

		window->clear();
		// Dessiner le sprite
		window->draw(sprite);

		scene.Render(window);
		window->display();
	}
	return 0;
}
