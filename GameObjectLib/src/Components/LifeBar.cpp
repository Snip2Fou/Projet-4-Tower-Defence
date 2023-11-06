#include "Components/LifeBar.h"
#include "Components/Player.h"

void LifeBar::Update(float deltaTimeMillisecondes, std::vector<GameObject*>* gameObjects)
{
	SetHp(GetOwner()->getComponent<Player>()->GetHp());
}
