#include "Scene.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

#include "Components/ShapeRenderer.h"
#include "Components/SquareCollider.h"
#include "Components/SpriteRenderer.h"
#include "Components/LifeBarRenderer.h"
#include "Components/ObjectName.h"

#include "Components/Enemy.h"
#include "Components/Player.h"
#include "Components/Button.h"
#include "Components/LifeBar.h"

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

GameObject* Scene::CreateEnemy(const ObjectName& name, const Maths::Vector2<float>& position, int hp, int speed, int damage)
{
	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(position);

	SpriteRenderer* spriteRenderer = gameObject->CreateComponent<SpriteRenderer>();
	if (GetLevel() == 1)
	{
		spriteRenderer->SetSprite(&texture["texture_enemy"], 1, 1);
	}
	else if (GetLevel() == 2)
	{
		spriteRenderer->SetSprite(&texture["texture_enemy"], 1, 1);
	}
	else if (GetLevel() == 3)
	{
		spriteRenderer->SetSprite(&texture["texture_enemy"], 0.5f, 0.5f);
	}

	SquareCollider* squareCollider = gameObject->CreateComponent<SquareCollider>();
	squareCollider->SetWidth(spriteRenderer->GetWidth());
	squareCollider->SetHeight(spriteRenderer->GetHeight());

	Enemy* enemy = gameObject->CreateComponent<Enemy>();
	enemy->SetHp(hp);
	enemy->SetSpeed(speed);
	enemy->SetDamage(damage);
	return gameObject;
}

GameObject* Scene::CreatePlayer(const ObjectName& name, const Maths::Vector2<float>& position, int hp, int speed, int damage)
{
	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(position);

	SpriteRenderer* spriteRenderer = gameObject->CreateComponent<SpriteRenderer>();
	spriteRenderer->SetSprite(&texture["texture_player"], 0.07f, 0.07f);

	SquareCollider* squareCollider = gameObject->CreateComponent<SquareCollider>();
	squareCollider->SetWidth(spriteRenderer->GetWidth());
	squareCollider->SetHeight(spriteRenderer->GetHeight());

	Player* player = gameObject->CreateComponent<Player>();
	player->SetHp(hp);
	player->SetSpeed(speed);
	player->SetDamage(damage);

	LifeBar* lifebar = gameObject->CreateComponent<LifeBar>();
	lifebar->SetHpMax(player->GetHp());
	lifebar->SetHp(player->GetHp());
	LifeBarRenderer* lifeBarRenderer = gameObject->CreateComponent<LifeBarRenderer>();
	lifeBarRenderer->SetSprite(&texture["texture_life_bar"], 1, 1);
	spriteRenderer->SetOrigin(player->GetPosition().GetX() / 2, player->GetPosition().GetY() / 2);

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
