#pragma once
#include "Scenes.h"

class Game {
public:
	const Maths::Vector2f HorizontalOrigin = Maths::Vector2f(5.f, 0.f);
	const Maths::Vector2f VerticalOrigin = Maths::Vector2f(0.f, 5.f);

	int largeur = 800;
	int longueur = 800;

	int gameOn();
	// Taille de la window
	
private:
	

	int frameRateLimit = 60;

};