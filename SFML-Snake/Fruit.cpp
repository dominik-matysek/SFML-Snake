#include "Fruit.h"
#include "Engine.h"

Fruit::Fruit(sf::Vector2f size, sf::Vector2i gridSize) :
	sf::RectangleShape(size),
	_gridSize(gridSize)
{
	setFillColor(sf::Color(159, 25, 27));
}

// Zwracamy true je¿eli jab³ko znajduje siê na danej pozycji
bool Fruit::Collides(sf::Vector2i gridPosition) const
{
	sf::Vector2i fruitGridPosition = Engine::GetInstance()->WorldPositionToGridPosition(getPosition());
	return gridPosition.x == fruitGridPosition.x && gridPosition.y == fruitGridPosition.y;
}

void Fruit::Spawn()
{
	sf::Vector2i gridPosition;
	do
	{
		// Szukamy losowo miêdzy granicami dopóki nie znajdziemy wolnej pozycji
		gridPosition = sf::Vector2i(rand() % (_gridSize.x - 1) + 1, rand() % (_gridSize.y - 1) + 1);
	} while (Engine::GetInstance()->Collides(gridPosition));

	setPosition(Engine::GetInstance()->GridPositionToWorldPosition(gridPosition));
}