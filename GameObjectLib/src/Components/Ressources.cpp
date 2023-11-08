#include "Components/Ressources.h"

std::string Ressources::SetName(std::string new_name)
{
	name = new_name;
	return name;
}

int Ressources::SetNombre(int new_nombre)
{
	nombre = new_nombre;
	return nombre;
}

int Ressources::SetType(int new_type)
{
	type = new_type;
	return type;
}