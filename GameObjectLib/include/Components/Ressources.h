#pragma once

#include "GameObject.h"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

class Ressources
{
public:
	Ressources() = default;
	~Ressources() = default;
	std::string GetName() { return name; }
	int GetNombre() { return nombre; }
	int GetType() { return type; }

private:
	std::string name;
	int nombre;
	int type;
};
