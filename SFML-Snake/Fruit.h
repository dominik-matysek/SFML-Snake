#pragma once

#include <SFML/Graphics.hpp>
#include "Collidable.h"

// Klasa odpowiedzialna za jab³ko
class Fruit : public sf::RectangleShape, public Collidable
{
private:
	sf::Vector2i _gridSize;

public:
	// Konstruktor jab³ka
	Fruit(sf::Vector2f size, sf::Vector2i gridSize);

	// Sprawdzanie kolizji

	virtual bool Collides(sf::Vector2i gridPosition) const;
	// Pojawianie siê jab³ka na losowej wolnej pozycji
	void Spawn();
};