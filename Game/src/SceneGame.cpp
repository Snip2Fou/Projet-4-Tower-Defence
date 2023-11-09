#include <chrono>

#include "eventGame.h"
#include "eventPause.h"
#include "Scenes.h"
#include "Game.h"
#include "EnemySpawn.h"
#include "TowerSpot.h"
#include "Button.h"
#include "BuildMenu.h"

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



	sf::Clock clock;
	auto time_for_enemy_spawn = std::chrono::high_resolution_clock::now();

	sf::Texture background = scene.GetTetxure()["texture_floor"];

	// Créer un sprite avec la texture chargée
	sf::Sprite sprite(background);

	TowerSpot spotClass;

	GameObject* spot1 = spotClass.createButtonObj(&scene, "Spot", 1);
	GameObject* spot2 = spotClass.createButtonObj(&scene, "Spot", 2);
	GameObject* spot3 = spotClass.createButtonObj(&scene, "Spot", 3);
	eventFunction.buttonList.push_back(spot1);
	eventFunction.buttonList.push_back(spot2);
	eventFunction.buttonList.push_back(spot3);

	GameObject* buttonBuildMenu = buttonClass.createButtonObj(&scene, "BuildMenu");
	eventFunction.buttonList.push_back(buttonBuildMenu);


	BuildMenu build_menu;
	GameObject* buttonTower1 = buttonClass.createButtonObj(&scene, "ButtonTower1");
	eventFunction.buttonList.push_back(buttonTower1);
	build_menu.SetButtonTower1(buttonTower1);

	GameObject* buttonTower2 = buttonClass.createButtonObj(&scene, "ButtonTower2");
	eventFunction.buttonList.push_back(buttonTower2);
	build_menu.SetButtonTower2(buttonTower2);

	GameObject* buttonTower3 = buttonClass.createButtonObj(&scene, "ButtonTower3");
	eventFunction.buttonList.push_back(buttonTower3);
	build_menu.SetButtonTower3(buttonTower3);

	clock.restart();

	GameObject* player = scene.CreatePlayer(ObjectName::PlayerName, Maths::Vector2f(375, 5), 200);
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
			sceneOn = eventFunction.loopEvent(player, 50, window, game.HorizontalOrigin, game.VerticalOrigin, &scene, deltaTimeMilliseconds, &pauseOn, &build_menu.isvisible); //Enlever pour pause

			time_for_enemy_spawn = enemySpawn.CheckIfIsTimeToEnemySpawn(&scene, time_for_enemy_spawn); //Enlever pour pause

			scene.Update(deltaTimeMilliseconds); //Enlever pour pause
			build_menu.Update(buttonBuildMenu);
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

		build_menu.Render(window);
		scene.Render(window);
		window->display();
	}
	return 0;
}
