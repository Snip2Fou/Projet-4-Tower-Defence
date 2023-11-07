#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>


#include "GameObject.h"
#include "Vector2.h"
#include "WindowConfig.h"
#include "Player.h"

class Input
{
protected:

    WindowConfig windowConfig;
    Maths::Vector2f MoveVector = Maths::Vector2f (7.f,7.f);

public:
    enum InputType { Keyboard, Mouse };

    InputType inputType;

    sf::Keyboard::Key key;
    sf::Mouse::Button mouseButton;

    bool inputBool;
    virtual void execute(GameObject* actor, float sizeActor, sf::RenderWindow* window, std::vector<GameObject*>* gameObjects) {};

    // Constructeur pour le clavier
    Input(sf::Keyboard::Key k1, bool ib)
        : inputType(Keyboard), key(k1), mouseButton(sf::Mouse::ButtonCount), inputBool(ib) {}

    // Constructeur pour la souris
    Input(sf::Mouse::Button mb, bool ib)
        : inputType(Mouse), key(sf::Keyboard::Unknown), mouseButton(mb), inputBool(ib) {}
};

class Build : public Input
{
public:
    Build()
        : Input(sf::Mouse::Left, false) {}

    void execute(GameObject* actor, float sizeActor, sf::RenderWindow* window, std::vector<GameObject*>* gameObjects) override
    {
        std::cout << "Pan !" << std::endl;
    }
};