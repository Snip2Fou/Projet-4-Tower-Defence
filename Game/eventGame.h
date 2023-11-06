#pragma once
#include "event.h"
#include "SFML/Audio.hpp"

class EventFunctionsGame {
private:
	sf::SoundBuffer* soundBufferFon;
	sf::Sound* soundFon;

public:
	EventFunctionsGame();
	~EventFunctionsGame();

	std::vector<Input*> createVectorInput();
	std::vector<Input*> inputList = createVectorInput();
	std::vector<GameObject*> buttonList;

	void eventCloseWindow(sf::RenderWindow* window);
	void eventKeyPressed(sf::Event event);
	void eventKeyReleased(sf::Event event);
	void angleWrite(float AngleMouseHor);
	void eventMouseRight(sf::Event event, GameObject* actor, sf::RenderWindow* window, const Maths::Vector2f HorizontalOrigin, const Maths::Vector2f VerticalOrigin);
	bool eventMouseLeft(sf::Event event, GameObject* actor, sf::RenderWindow* window, Scene* scene, float deltaTimeMilliseconds, sf::Vector2i mousePosition);
	bool eventMousePressed(sf::Event event, GameObject* actor, sf::RenderWindow* window, const Maths::Vector2f HorizontalOrigin, const Maths::Vector2f VerticalOrigin, Scene* scene, float deltaTimeMilliseconds, sf::Vector2i mousePosition);
	void eventMouseRelease(sf::Event event);
	void eventExecute(GameObject* actor, float sizeActor, sf::RenderWindow* window, std::vector<GameObject*>* gameObjects);
	void PlaySound();

	void eventChangeColorButton(GameObject* buttonCheck, sf::Color colorChange);
	bool eventCollisionMouseButton(GameObject* buttonCheck, sf::Vector2i mousePosition);
	void eventHoverButton(GameObject* buttonCheck, sf::Vector2i mousePosition);
	bool eventCheckClickButton(sf::Vector2i mousePosition, sf::Event event, sf::RenderWindow* window);
	std::string eventClickButton(GameObject* buttonCheck, sf::Vector2i mousePosition);



	bool loopEvent(GameObject* actor, float sizeActor, sf::RenderWindow* window, const Maths::Vector2f HorizontalOrigin, const Maths::Vector2f VerticalOrigin, Scene* scene, float deltaTimeMilliseconds, bool* pauseOn);
};