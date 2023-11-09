#pragma once

#include "Component.h"

class Ressources : public Component
{
public:
	Ressources() = default;
	~Ressources() = default;
	std::string GetName() { return name; }
	int GetNombre() { return nombre; }
	int GetType() { return type; }
	std::string SetName(std::string new_name);
	int SetNombre(int new_nombre);
	int SetType(int new_type);

private:
	std::string name;
	int nombre = 0;
	int type = 0;
};
