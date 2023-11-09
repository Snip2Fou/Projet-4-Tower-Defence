#include "Components/Ressources.h"


void Ressources::SetName(std::string new_name)
{
	name = new_name;
}

void Ressources::SetNombre(float new_nombre)
{
	nombre += new_nombre;
}

void Ressources::SetType(int new_type)
{
	type = new_type;
}