#pragma once

#include "SFML/System.hpp"

// Klasa abstrakcyjna dla obiektów które mog¹ wejœæ w kolizjê
class Collidable
{
public:
	// Kolizja na bazie "kratek" int
	virtual bool Collides(sf::Vector2i gridPosition) const = 0;
};