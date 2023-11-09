 #include "Scene.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

#include "Components/ShapeRenderer.h"
#include "Components/SquareCollider.h"
#include "Components/SpriteRenderer.h"
#include "Components/LifeBarRenderer.h"
#include "Components/RessourcesRenderer.h"

#include "Components/Enemy.h"
#include "Components/Player.h"
#include "Components/Button.h"
#include "Components/LifeBar.h"
#include "Components/ObjectName.h"
#include "GameObject.h"


void Scene::Update(float deltaTimeMillisecondes)
{
	for (GameObject* const& gameObject : gameObjects)
	{
		gameObject->Update(deltaTimeMillisecondes, &gameObjects);
	}
	//for (int i = 0; i < gameObjects.size(); i++)
	//{
	//	gameObjects[i]->Update(deltaTimeMillisecondes, &gameObjects);
	//}
}

void Scene::Render(sf::RenderWindow* _window)
{
	for (GameObject* const& gameObject : gameObjects)
	{
		gameObject->Render(_window);
	}
}

GameObject* Scene::CreateGameObject(const ObjectName& _name)
{
	auto gameObject = new GameObject();
	gameObject->SetName(_name);
	gameObjects.push_back(gameObject);
	return gameObject;
}

GameObject* Scene::CreateEnemy(const ObjectName& name, const Maths::Vector2<float>& position, int hp, int speed, int damage, std::string sprite)
{
	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(position);

	SpriteRenderer* spriteRenderer = gameObject->CreateComponent<SpriteRenderer>();
	spriteRenderer->SetSprite(&texture[sprite], 1, 1);

	SquareCollider* squareCollider = gameObject->CreateComponent<SquareCollider>();
	squareCollider->SetWidth(spriteRenderer->GetWidth());
	squareCollider->SetHeight(spriteRenderer->GetHeight());

	Enemy* enemy = gameObject->CreateComponent<Enemy>();
	enemy->SetHp(hp);
	enemy->SetSpeed(speed);
	enemy->SetDamage(damage);
	return gameObject;
}

GameObject* Scene::CreatePlayer(const ObjectName& name, const Maths::Vector2<float>& position, int hp)
{
	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(position);

	Player* player = gameObject->CreateComponent<Player>();
	player->SetHp(hp);

	LifeBar* lifebar = gameObject->CreateComponent<LifeBar>();
	lifebar->SetHpMax(player->GetHp());
	lifebar->SetHp(player->GetHp());
	LifeBarRenderer* lifeBarRenderer = gameObject->CreateComponent<LifeBarRenderer>();
	lifeBarRenderer->SetSprite(&texture["texture_life_bar"], 1, 1);

	GameObject* gameObject2 = CreateGameObject(ObjectName::RessourceName);
	gameObject2->SetPosition(Maths::Vector2f(10, 50));
	Ressources* ressource1 = gameObject2->CreateComponent<Ressources>();
	ressource1->SetName("Bois");
	ressource1->SetType(1);

	/*RessourcesRenderer* ressourceRenderer1 = gameObject2->CreateComponent<RessourcesRenderer>();
	ressourceRenderer1->SetSprite(&texture["texture_ressource1"], 1, 1);*/

	player->SetRessources1(gameObject2);


	GameObject* gameObject3 = CreateGameObject(ObjectName::RessourceName);
	gameObject3->SetPosition(Maths::Vector2f(10, 90));
	Ressources* ressource2 = gameObject3->CreateComponent<Ressources>();
	ressource2->SetName("Pierre");
	ressource2->SetType(2);
	
	/*RessourcesRenderer* ressourceRenderer2 = player->GetRessource2()->CreateComponent<RessourcesRenderer>();
	ressourceRenderer2->SetSprite(&texture["texture_ressource2"], 1, 1);*/
	player->SetRessources2(gameObject3);

	return gameObject;
}

GameObject* Scene::CreateWall(const ObjectName& name, const Maths::Vector2<float>& position)
{
	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(position);

	SpriteRenderer* spriteRenderer = gameObject->CreateComponent<SpriteRenderer>();
	spriteRenderer->SetSprite(&texture["texture_wall-1"], 1, 1);

	SquareCollider* squareCollider = gameObject->CreateComponent<SquareCollider>();
	squareCollider->SetWidth(spriteRenderer->GetWidth());
	squareCollider->SetHeight(spriteRenderer->GetHeight());

	return gameObject;
}

GameObject* Scene::CreateButton(const ObjectName& name, const Maths::Vector2<float>& position, const sf::Color color, const sf::Color colorHover, const sf::Color colorClick, sf::Vector2f size, std::string type)
{
	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(position);

	ShapeRenderer* shapeRenderer = gameObject->CreateComponent<ShapeRenderer>();
	shapeRenderer->SetColor(color);
	shapeRenderer->SetSize(size);

	Button* button = gameObject->CreateComponent<Button>();
	button->Size = size;
	button->position = position;
	button->color = color;
	button->colorNothing = color;
	button->colorHover = colorHover;
	button->colorClick = colorClick;
	button->type = type;

	return gameObject;
}

void Scene::CreateShape(const ObjectName& name, const sf::Color color, const sf::Vector2f size) {
	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(Maths::Vector2<float>(size.x/2, size.y/2));

	ShapeRenderer* shapeRenderer = gameObject->CreateComponent<ShapeRenderer>();
	shapeRenderer->SetColor(color);
	shapeRenderer->SetSize(size);
}

int Scene::SetTexture(std::string nom_texture, std::string chemin_fichier)
{
	sf::Texture new_texture;

	if (!new_texture.loadFromFile(chemin_fichier))
	{
		return EXIT_FAILURE;
	}
	new_texture.setSmooth(true);
	texture[nom_texture] = new_texture;

	return EXIT_SUCCESS;
}
