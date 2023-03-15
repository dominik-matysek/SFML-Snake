#pragma once

#include "SFML/System.hpp"

// Klasa abstrakcyjna dla obiekt�w kt�re mog� wej�� w kolizj�
class Collidable
{
public:
	// Kolizja na bazie "kratek" int
	virtual bool Collides(sf::Vector2i gridPosition) const = 0;
};