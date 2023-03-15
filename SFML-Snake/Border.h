#pragma once

#include <SFML/Graphics.hpp>
#include "Collidable.h"

// Klasa odpowiedzialna za granicê mapy
class Border : public sf::Drawable, public Collidable
{
public:
	// Konstruktor granicy
	Border(sf::Vector2i gridSize, sf::Vector2i gameArea);

	// Sprawdzanie kolizji
	virtual bool Collides(sf::Vector2i gridPosition) const;

protected:
	// Do rysowania kratek
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	// Dodawanie pojedynczej kratki granicy
	void AddCell(float cellSize, float posX, float posY);

	std::vector<std::shared_ptr<sf::RectangleShape>> _cells;
	sf::Vector2i _gridSize;

	// Do zamiany kolorów kratek
	const std::vector<sf::Color> _colors = { sf::Color::Color(30, 30, 30), sf::Color::Color(60, 60, 60) };
};