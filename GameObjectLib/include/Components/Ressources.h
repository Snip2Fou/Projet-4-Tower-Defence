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

	void Update(float deltaTimeMillisecondes, std::vector<GameObject*>* gameObjects) override;

private:
	std::string name;
	int nombre;
	int type;
};
