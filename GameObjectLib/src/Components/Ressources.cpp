#include "Components/Ressources.h"
#include <iostream>

std::string Ressources::SetName(std::string new_name)
{
	name = new_name;
	return name;
}

int Ressources::SetNombre(int new_nombre)
{
	nombre = nombre + new_nombre;
	return nombre;
	std::cout << nombre << std::endl;
}

int Ressources::SetType(int new_type)
{
	type = new_type;
	return type;
}