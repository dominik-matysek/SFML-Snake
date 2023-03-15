#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Updatable.h"
#include "Collidable.h"
#include "Fruit.h"

// Klasa odpowiedzialna za posta� gracza (w�a)
class Snake : public sf::Drawable, public Updatable, public Collidable
{
public:
	// Konstruktor przyjmuj�cy rozmiar postaci, pozycj� w jakiej zaczyna i kierunek
	Snake(int size, float length, sf::Vector2f position, sf::Vector2i direction);

	virtual void Update(float deltaTime);
	virtual bool Collides(sf::Vector2i gridPosition) const;

	// Pozycja na jakiej znajduje si� prz�d postaci (g�owa)
	const sf::Vector2f& GetHeadPosition() const;

	// Przesuwanie ca�ego cia�a postaci w odpowiednim kierunku
	void Move(sf::Vector2f movement);
	const sf::Vector2i& GetDirection() const;

	void SetDirection(const sf::Vector2i& direction);

	// Wzrost postaci w�a po zebraniu przedmiotu
	void Grow();
	// �mier� postaci
	void Die();
	// True je�eli posta� umar�a
	bool IsDead() const;
	// Pr�dko�� postaci
	float GetMoveSpeed() const;
	// Ustawienie owoca
	void SetFruit(std::shared_ptr<Fruit> fruit);

	// True je�eli osi�gni�to maksymaln� pr�dko��
	bool ReachedMaxSpeed() const;

protected:
	// Do rysowania postaci
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	// Sprawdzanie czy posta� mo�e i�� w konkretnym kierunku (aby unikn�� cofania si� postaci)
	bool CanMoveTowards(sf::Vector2i direction) const;

	// Posta� w�a sk�ada si� z wektora okr�g�w
	std::vector<sf::CircleShape> _body;
	sf::Vector2i _direction;

	bool _dead;

	// Zmiana kolor�w cia�a w�a
	std::vector<sf::Color> _colors = { sf::Color(0, 109, 75), sf::Color(75, 204, 75) };

	float _initialMoveInterval = .2f;
	// Im mniejszy interwa�, tym wi�ksza pr�dko�c
	float _moveInterval = _initialMoveInterval;
	float _moveTimer = 0.f;
	// Za ka�dym razem jak posta� podniesie przedmiot, moveInterval zmieni si� o poni�sz� warto��
	float _moveIntervalMultiplier = .95f;
	// Najmnieszy interwa� = najwi�ksza pr�dko��
	float _minMoveInterval = _initialMoveInterval / 3.5f;

	std::shared_ptr<Fruit> _fruit;
};