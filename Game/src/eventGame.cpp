#include "eventGame.h"
#include "button.h"
#include "ShapeRenderer.h"
#include "TowerSpot.h"

EventFunctionsGame::EventFunctionsGame()
{
	soundBufferFon = new sf::SoundBuffer;
	if (!soundBufferFon->loadFromFile("Assets/Son/chill-drum-loop-6887.wav")) { 
		std::cout << "erreur de chargement du fichier" << std::endl; 
	}
	soundFon = new sf::Sound; 
	PlaySound();
}

EventFunctionsGame::~EventFunctionsGame()
{
	delete soundBufferFon;
	delete soundFon;
	soundFon = nullptr;
	soundBufferFon = nullptr;
}

void EventFunctionsGame::eventChangeColorButton(GameObject* buttonCheck, sf::Color colorChange) {
	Button* buttonCheckButton = buttonCheck->getComponent<Button>();
	ShapeRenderer* buttonCheckShape = buttonCheck->getComponent<ShapeRenderer>();

	buttonCheckButton->color = colorChange;
	buttonCheckShape->SetColor(colorChange);
}

bool EventFunctionsGame::eventCollisionMouseButton(GameObject* buttonCheck, sf::Vector2i mousePosition) {
	Button* buttonCheckButton = buttonCheck->getComponent<Button>();

	sf::Vector2f position(buttonCheckButton->position.x, buttonCheckButton->position.y);
	float hauteur = buttonCheckButton->Size.y;
	float largeur = buttonCheckButton->Size.x;
	sf::Vector2f ShapeStart(position.x - largeur / 2, position.y - hauteur / 2);
	sf::Vector2f ShapeEnd(ShapeStart.x + largeur, ShapeStart.y + hauteur);

	if (
		(mousePosition.x > ShapeStart.x) && (mousePosition.x < ShapeEnd.x) &&
		(mousePosition.y > ShapeStart.y) && (mousePosition.y < ShapeEnd.y)
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void EventFunctionsGame::eventHoverButton(GameObject* buttonCheck, sf::Vector2i mousePosition) {
	Button* buttonCheckButton = buttonCheck->getComponent<Button>();

	if (eventCollisionMouseButton(buttonCheck, mousePosition) == true)
	{
		eventChangeColorButton(buttonCheck, buttonCheckButton->colorHover);
	}
	else
	{
		eventChangeColorButton(buttonCheck, buttonCheckButton->colorNothing);
	}

}

bool EventFunctionsGame::eventCheckClickButton(sf::Vector2i mousePosition, sf::Event event, sf::RenderWindow* window, std::string buttontype, GameObject* actor) {
	std::vector<std::string> returnWhat;

	for (GameObject* buttonCheck : buttonList)
	{
		std::string response = eventClickButton(buttonCheck, mousePosition);
		if (response == "Spot") {
			if (buttonCheck->getComponent<Button>()->is_activate) {
				if (buttonCheck->getComponent<Button>()->is_selected) {
					buttonCheck->getComponent<Button>()->is_selected = false;
					actor->getComponent<Player>()->SetChoosenSpotToNullPtr();
					response = "";
				}
				else {
					if (actor->getComponent<Player>()->GetChoosenSpot() != nullptr) {
						actor->getComponent<Player>()->GetChoosenSpot()->getComponent<Button>()->is_selected = false;
						eventChangeColorButton(actor->getComponent<Player>()->GetChoosenSpot(), actor->getComponent<Player>()->GetChoosenSpot()->getComponent<Button>()->colorNothing);
					}
					buttonCheck->getComponent<Button>()->is_selected = true;
					actor->getComponent<Player>()->SetChoosenSpot(buttonCheck);
				}
			}
		}else if (response == "ButtonTower1" || response == "ButtonTower2" || response == "ButtonTower3") {
			if (buttonCheck->getComponent<Button>()->is_selected) {
				buttonCheck->getComponent<Button>()->is_selected = false;
				actor->getComponent<Player>()->SetChoosenTowerToNullPtr();
			}
			else {
				if (actor->getComponent<Player>()->GetChoosenTower() != nullptr) {
					actor->getComponent<Player>()->GetChoosenTower()->getComponent<Button>()->is_selected = false;
					eventChangeColorButton(actor->getComponent<Player>()->GetChoosenTower(), actor->getComponent<Player>()->GetChoosenTower()->getComponent<Button>()->colorNothing);
				}
				buttonCheck->getComponent<Button>()->is_selected = true;
				actor->getComponent<Player>()->SetChoosenTower(buttonCheck);
			}
		}
		else if(response != "") {
			if (buttonCheck->getComponent<Button>()->is_selected) {
				buttonCheck->getComponent<Button>()->is_selected = false;
			}
			else {
				buttonCheck->getComponent<Button>()->is_selected = true;
			}
		}
		returnWhat.push_back(response);
	}

	for (std::string returnWhatBool : returnWhat)
	{
		if (returnWhatBool == buttontype) {
			return true;
		}
	}
	return false;
}

bool EventFunctionsGame::eventCheckClickButtonRight(sf::Vector2i mousePosition, sf::Event event, sf::RenderWindow* window, std::string buttontype, GameObject* actor, Scene* scene) {
	std::vector<std::string> returnWhat;

	for (GameObject* buttonCheck : buttonList)
	{
		std::string response = eventClickButton(buttonCheck, mousePosition);

		if (response == "Spot") {
			if (!buttonCheck->getComponent<Button>()->is_activate) {
				if (buttonCheck->getComponent<Button>()->target->getComponent<Tower>()->GetType() == TowerType::ArcherType) {
					actor->getComponent<Player>()->GetRessource1()->getComponent<Ressources>()->SetNombre(600);
				}else if (buttonCheck->getComponent<Button>()->target->getComponent<Tower>()->GetType() == TowerType::MageType) {
					actor->getComponent<Player>()->GetRessource1()->getComponent<Ressources>()->SetNombre(1500);
				}else if (buttonCheck->getComponent<Button>()->target->getComponent<Tower>()->GetType() == TowerType::BomberType) {
					actor->getComponent<Player>()->GetRessource1()->getComponent<Ressources>()->SetNombre(3000);
				}
				buttonCheck->getComponent<Button>()->is_activate = true;
				buttonCheck->getComponent<Button>()->is_selected = false;
				buttonCheck->getComponent<Button>()->target->RemoveComponent(buttonCheck->getComponent<Tower>());
				buttonCheck->getComponent<Button>()->target->RemoveComponent(buttonCheck->getComponent<ShapeRenderer>());
				for (auto it =  actor->getComponent<Player>()->GetTowers()->begin(); it != actor->getComponent<Player>()->GetTowers()->end(); ++it)
				{
					if (*it == buttonCheck->getComponent<Button>()->target)
					{
						actor->getComponent<Player>()->GetTowers()->erase(it);
						break;
					}
				}
				for (auto it = scene->GetGameObjects()->begin(); it != scene->GetGameObjects()->end(); ++it)
				{
					if (*it == buttonCheck->getComponent<Button>()->target)
					{
						delete buttonCheck->getComponent<Button>()->target;
						scene->GetGameObjects()->erase(it);
						return true;
					}
				}
				buttonCheck->getComponent<Button>()->target = nullptr;
				eventChangeColorButton(buttonCheck, buttonCheck->getComponent<Button>()->colorNothing);
			}
		}

		returnWhat.push_back(response);
	}

	for (std::string returnWhatBool : returnWhat)
	{
		if (returnWhatBool == buttontype) {
			return true;
		}
	}
	return false;
}

std::string EventFunctionsGame::eventClickButton(GameObject* buttonCheck, sf::Vector2i mousePosition) {
	Button* buttonCheckButton = buttonCheck->getComponent<Button>();

	if (eventCollisionMouseButton(buttonCheck, mousePosition) == true)
	{
		if (buttonCheck->getComponent<Button>()->is_selected) {
			eventChangeColorButton(buttonCheck, buttonCheck->getComponent<Button>()->colorNothing);
		}
		else {
			eventChangeColorButton(buttonCheck, buttonCheck->getComponent<Button>()->colorClick);
		}
		return buttonCheckButton->type;
	}
	return "";
}

void EventFunctionsGame::eventCloseWindow(sf::RenderWindow* window) {
	window->close();
}

void EventFunctionsGame::eventKeyPressed(sf::Event event) {
	for (Input* input : inputList)
	{
		if (input->inputType == Input::Keyboard && input->key == event.key.code)
		{
			input->inputBool = true;
		}
	}
}

void EventFunctionsGame::eventKeyReleased(sf::Event event) {
	for (Input* input : inputList)
	{
		if (input->inputType == Input::Keyboard && input->key == event.key.code)
		{
			input->inputBool = false;
		}
	}
}

void EventFunctionsGame::angleWrite(float AngleMouseHor) {
	if (AngleMouseHor > 30 && AngleMouseHor <= 60)
	{
		std::cout << "Right" << std::endl << std::endl;
	}
	else if (AngleMouseHor > 60 && AngleMouseHor <= 120)
	{
		std::cout << std::endl << std::endl;
	}
	else if (AngleMouseHor > 120 && AngleMouseHor <= 150)
	{
		std::cout << "Left" << std::endl << std::endl;
	}
}

void EventFunctionsGame::eventMouseRight(sf::Event event, GameObject* actor, sf::RenderWindow* window, const Maths::Vector2f HorizontalOrigin, const Maths::Vector2f VerticalOrigin, std::string buttontype, Scene* scene) {
	if (event.mouseButton.button == sf::Mouse::Right) {

		sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
		
		eventCheckClickButtonRight(mousePosition, event, window, buttontype, actor, scene);

	}
}

bool EventFunctionsGame::eventMouseLeft(sf::Event event, GameObject* actor, sf::RenderWindow* window, Scene* scene, float deltaTimeMilliseconds, sf::Vector2i mousePosition, std::string buttontype)
{
	if (event.mouseButton.button == sf::Mouse::Left)
	{
		if (eventCheckClickButton(mousePosition, event, window, buttontype, actor))
		{
			return true;
		}

		sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
		
		return false;
	}
	return false;
}


bool EventFunctionsGame::eventMousePressed(sf::Event event, GameObject* actor, sf::RenderWindow* window, const Maths::Vector2f HorizontalOrigin, const Maths::Vector2f VerticalOrigin, Scene* scene, float deltaTimeMilliseconds, sf::Vector2i mousePosition, std::string buttontype) {
	//for (Input* input : inputList)
	//{
	//	if (input->inputType == Input::Mouse && input->mouseButton == event.mouseButton.button)
	//	{
	//		input->inputBool = true;
	//	}
	//}
	eventMouseRight(event, actor, window, HorizontalOrigin, VerticalOrigin, buttontype, scene);
	return eventMouseLeft(event, actor, window, scene, deltaTimeMilliseconds, mousePosition, buttontype);
}

void EventFunctionsGame::eventMouseRelease(sf::Event event)  {
	if (event.mouseButton.button == sf::Mouse::Left) {
		// Parcourir les entr�es du souris
		for (Input* input : inputList)
		{
			if (input->inputType == Input::Mouse && input->mouseButton == event.mouseButton.button)
			{
				input->inputBool = false;
			}
		}
	}
}

void EventFunctionsGame::eventExecute(GameObject* actor, float sizeActor, sf::RenderWindow* window, std::vector<GameObject*>*gameObjects) {
	for (Input* input : inputList)
	{
		if (input->inputBool)
		{
			input->execute(actor, sizeActor, window, gameObjects);
		}
	}
}

std::vector<Input*> EventFunctionsGame::createVectorInput() {

	std::vector<Input*> inputListCreation;

	// Remplir le vecteur avec les entr�es d�sir�es
	inputListCreation.push_back(new Build());

	return inputListCreation;
}

void EventFunctionsGame::PlaySound()
{
	soundFon->setBuffer(*soundBufferFon);
	soundFon->play();
}



bool EventFunctionsGame::loopEvent(GameObject* actor, float sizeActor, sf::RenderWindow* window, const Maths::Vector2f HorizontalOrigin, const Maths::Vector2f VerticalOrigin, Scene* scene, float deltaTimeMilliseconds, bool *pauseOn, bool *buildMenuvisible){
	sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
	/*eventHoverButton(buttonList[0], mousePosition);*/

	sf::Event event;
	while (window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			eventCloseWindow(window);
			return false;
		}


		else if (event.type == sf::Event::KeyPressed) {
			eventKeyPressed(event);
			actor->getComponent<Player>()->PlaySound();
		}

		else if (event.type == sf::Event::KeyReleased) {
			eventKeyReleased(event);
			actor->getComponent<Player>()->StopSound();
		}

		else if (event.type == sf::Event::MouseButtonPressed) {
			*pauseOn = eventMousePressed(event, actor, window, HorizontalOrigin, VerticalOrigin, scene, deltaTimeMilliseconds, mousePosition, "Pause");
			bool buttonOpenBuildMenu = eventMousePressed(event, actor, window, HorizontalOrigin, VerticalOrigin, scene, deltaTimeMilliseconds, mousePosition, "BuildMenu");
			bool spotOpenBuildMenu = eventMousePressed(event, actor, window, HorizontalOrigin, VerticalOrigin, scene, deltaTimeMilliseconds, mousePosition, "Spot");
			std::cout << spotOpenBuildMenu << std::endl;
			if (*buildMenuvisible == false && (buttonOpenBuildMenu == true || spotOpenBuildMenu== true)) {
				*buildMenuvisible = true;
			}
			else if (*buildMenuvisible == true && spotOpenBuildMenu == true) {
				*buildMenuvisible = true;
			}
			else if (*buildMenuvisible == true && (buttonOpenBuildMenu == true || spotOpenBuildMenu == true)) {
				*buildMenuvisible = false;
			}
		}

		else if (event.type == sf::Event::MouseButtonReleased) {
			eventMouseRelease(event);
		}
	}

	// Parcourir les entr�es du souris
	eventExecute(actor, sizeActor, window, scene->GetGameObjects());
	return true;
}