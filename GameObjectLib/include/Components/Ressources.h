#pragma once
#include <iostream>
#include "GameObject.h"

class Ressources : public Component
{
public:
	std::string GetName() { return name; }
	int GetNombre() { return nombre; }
	int GetType() { return type; }
	void SetName(std::string new_name);
	void SetNombre(float new_nombre);
	void SetType(int new_type);

private:
	std::string name;
	float nombre = 0;
	int type = 0;
};
