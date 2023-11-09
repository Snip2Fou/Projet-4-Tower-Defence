#include "BuildMenu.h"
#include <iostream>
#include "Components/Button.h"

BuildMenu::BuildMenu() {
	shape = new sf::RectangleShape();
}

void BuildMenu::Update(GameObject* buttonBuildMenu){
	if (isvisible && position.y > 700 ) {
		position.SetY(position.y - 2);
		buttonBuildMenu->SetPosition(Maths::Vector2f(buttonBuildMenu->GetPosition().GetX(), buttonBuildMenu->GetPosition().GetY() - 2));
		GetButtonTower1()->SetPosition(Maths::Vector2f(GetButtonTower1()->GetPosition().GetX(), GetButtonTower1()->GetPosition().GetY() - 2));
		GetButtonTower2()->SetPosition(Maths::Vector2f(GetButtonTower2()->GetPosition().GetX(), GetButtonTower2()->GetPosition().GetY() - 2));
		GetButtonTower3()->SetPosition(Maths::Vector2f(GetButtonTower3()->GetPosition().GetX(), GetButtonTower3()->GetPosition().GetY() - 2));
	}else if(!isvisible && position.y < 800) {
		position.SetY(position.y + 2);
		buttonBuildMenu->SetPosition(Maths::Vector2f(buttonBuildMenu->GetPosition().GetX(), buttonBuildMenu->GetPosition().GetY() + 2));
		GetButtonTower1()->SetPosition(Maths::Vector2f(GetButtonTower1()->GetPosition().GetX(), GetButtonTower1()->GetPosition().GetY() + 2));
		GetButtonTower2()->SetPosition(Maths::Vector2f(GetButtonTower2()->GetPosition().GetX(), GetButtonTower2()->GetPosition().GetY() + 2));
		GetButtonTower3()->SetPosition(Maths::Vector2f(GetButtonTower3()->GetPosition().GetX(), GetButtonTower3()->GetPosition().GetY() + 2));
	}
	buttonBuildMenu->getComponent<Button>()->position.SetY(buttonBuildMenu->GetPosition().GetY());
	GetButtonTower1()->getComponent<Button>()->position.SetY(GetButtonTower1()->GetPosition().GetY());
	GetButtonTower2()->getComponent<Button>()->position.SetY(GetButtonTower2()->GetPosition().GetY());
	GetButtonTower3()->getComponent<Button>()->position.SetY(GetButtonTower3()->GetPosition().GetY());
}

void BuildMenu::Render(sf::RenderWindow* _window){

		shape->setSize(size);
		shape->setPosition(position.x, position.y);
		shape->setFillColor(color);

		_window->draw(*shape);
}