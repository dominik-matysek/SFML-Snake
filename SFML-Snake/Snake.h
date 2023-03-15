#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Updatable.h"
#include "Collidable.h"
#include "Fruit.h"

// Klasa odpowiedzialna za postaæ gracza (wê¿a)
class Snake : public sf::Drawable, public Updatable, public Collidable
{
public:
	// Konstruktor przyjmuj¹cy rozmiar postaci, pozycjê w jakiej zaczyna i kierunek
	Snake(int size, float length, sf::Vector2f position, sf::Vector2i direction);

	virtual void Update(float deltaTime);
	virtual bool Collides(sf::Vector2i gridPosition) const;

	// Pozycja na jakiej znajduje siê przód postaci (g³owa)
	const sf::Vector2f& GetHeadPosition() const;

	// Przesuwanie ca³ego cia³a postaci w odpowiednim kierunku
	void Move(sf::Vector2f movement);
	const sf::Vector2i& GetDirection() const;

	void SetDirection(const sf::Vector2i& direction);

	// Wzrost postaci wê¿a po zebraniu przedmiotu
	void Grow();
	// Œmieræ postaci
	void Die();
	// True je¿eli postaæ umar³a
	bool IsDead() const;
	// Prêdkoœæ postaci
	float GetMoveSpeed() const;
	// Ustawienie owoca
	void SetFruit(std::shared_ptr<Fruit> fruit);

	// True je¿eli osi¹gniêto maksymaln¹ prêdkoœæ
	bool ReachedMaxSpeed() const;

protected:
	// Do rysowania postaci
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	// Sprawdzanie czy postaæ mo¿e iœæ w konkretnym kierunku (aby unikn¹æ cofania siê postaci)
	bool CanMoveTowards(sf::Vector2i direction) const;

	// Postaæ wê¿a sk³ada siê z wektora okrêgów
	std::vector<sf::CircleShape> _body;
	sf::Vector2i _direction;

	bool _dead;

	// Zmiana kolorów cia³a wê¿a
	std::vector<sf::Color> _colors = { sf::Color(0, 109, 75), sf::Color(75, 204, 75) };

	float _initialMoveInterval = .2f;
	// Im mniejszy interwa³, tym wiêksza prêdkoœc
	float _moveInterval = _initialMoveInterval;
	float _moveTimer = 0.f;
	// Za ka¿dym razem jak postaæ podniesie przedmiot, moveInterval zmieni siê o poni¿sz¹ wartoœæ
	float _moveIntervalMultiplier = .95f;
	// Najmnieszy interwa³ = najwiêksza prêdkoœæ
	float _minMoveInterval = _initialMoveInterval / 3.5f;

	std::shared_ptr<Fruit> _fruit;
};