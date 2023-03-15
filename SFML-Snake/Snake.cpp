#include "Snake.h"
#include "Engine.h"
#include "GameData.h"

Snake::Snake(int length, float radius, sf::Vector2f position, sf::Vector2i direction) :
	_body(1),
	_direction(direction),
	_dead(false)
{
	_body[0] = sf::CircleShape(radius);
	_body[0].setPosition(position);
	_body[0].setFillColor(sf::Color(255, 165, 0));
	// W�� ro�nie do wybranej w metodach innych klas warto�ci ( np. chcemy �eby zacz�� maj�c d�ugo�� = 3 w trakcie rozgrywki, ale w trakcie animacji w menu d�ugo�c = 12)
	while (_body.size() < length)
	{
		Grow();
	}
	_moveInterval = _initialMoveInterval;
}

void Snake::Update(float deltaTime)
{
	// Je�eli nie �yje, koniec!
	if (IsDead()) return;

	_moveTimer += deltaTime;
	Engine* engine = Engine::GetInstance();
	float cellSize = engine->GetCellSize();

	if (_moveTimer > _moveInterval)
	{
		// Sprawdzamy kolizj� zanim do niej faktycznie dojdzie (je�eli nastepna kratka na kt�r� trafi posta� jest zaj�ta, dochodzi do kolizji)
		sf::Vector2f nextHeadPosition = GetHeadPosition() + sf::Vector2f(_direction.x * cellSize, _direction.y * cellSize);
		sf::Vector2i nextHeadGridPosition = engine->WorldPositionToGridPosition(nextHeadPosition);

		sf::Vector2i lastPartGridPosition = engine->WorldPositionToGridPosition(_body[_body.size() - 1].getPosition());

		// Ostatnia cz�c postaci jest wykluczona z kolizji, poniewa� porusza si� do przodu
		if (engine->Collides(nextHeadGridPosition) && nextHeadGridPosition != lastPartGridPosition)
		{
			Die();
			return;
		}

		// Je�eli dochodzi do kolizji z przedmiotem, w�� ro�nie, punktacja si� zwi�ksza, przedmiot pojawia si� ponownie w losowym dost�pnym miejscu
		if (_fruit && _fruit->Collides(nextHeadGridPosition))
		{
			Grow();
			++GameData::Score;
			_fruit->Spawn();
		}

		Move(sf::Vector2f(_direction.x * cellSize, _direction.y * cellSize));
		_moveTimer = 0.f;
	}
}

bool Snake::Collides(sf::Vector2i gridPosition) const
{
	int max = (int)_body.size();
	for (int i = 0; i < max; ++i)
	{
		sf::Vector2i bodyPartPosition = Engine::GetInstance()->WorldPositionToGridPosition(_body[i].getPosition());
		if (bodyPartPosition.x == gridPosition.x && bodyPartPosition.y == gridPosition.y)
		{
			return true;
		}
	}

	return false;
}

const sf::Vector2f& Snake::GetHeadPosition() const
{
	return _body[0].getPosition();
}

void Snake::Move(sf::Vector2f movement)
{
	for (int i = (int)_body.size() - 1; i >= 0; --i)
	{
		if (i == 0)
		{
			// G�owa przesuwa si� w odpowiedni� stron�
			_body[i].move(movement);
		}
		else
		{
			// Reszta cia�a pod��a za pozosta�ymi
			_body[i].setPosition(_body[(size_t)i - 1].getPosition());
		}
	}
}

const sf::Vector2i& Snake::GetDirection() const
{
	return _direction;
}

// Sprawdzamy czy w�� mo�e porusza� si� w danym kierunku
void Snake::SetDirection(const sf::Vector2i& direction)
{
	if (!CanMoveTowards(direction))
	{
		return;
	}
	_direction = direction;
}

void Snake::Grow()
{
	float radius = _body[0].getRadius();
	float size = radius * 2.f;
	size_t bodyLength = _body.size();

	sf::CircleShape bodypart = sf::CircleShape(radius);
	sf::CircleShape previous = _body[bodyLength - 1];
	sf::Vector2f position = previous.getPosition();
	sf::Vector2i gridPosition = Engine::GetInstance()->WorldPositionToGridPosition(position);

	sf::Vector2i direction = bodyLength > 1
		//Je�eli jest wi�cej ni� dwie cz�ci cia�a, wybieramy kierunek pomi�dzy dwoma ostatnimi
		? Engine::GetInstance()->WorldPositionToGridPosition(_body[bodyLength - 2].getPosition()) - gridPosition
		// Je�eli jest tylko g�owa, bierzemy kierunek poruszania si�
		: _direction;

	// Bierzemy przeciwny kierunek, poniewa� w�� ro�nie od ko�ca (od ogona)
	bodypart.setPosition(position - sf::Vector2f(direction.x * size, direction.y * size));
	bodypart.setFillColor(_colors[_body.size() % _colors.size()]);
	_body.push_back(bodypart);

	// Razem z wzrostem ro�nie pr�dko�c
	_moveInterval *= _moveIntervalMultiplier;
	if (_moveInterval < _minMoveInterval)
	{
		_moveInterval = _minMoveInterval;
	}
}

void Snake::Die()
{
	_dead = true;
	// Je�eli w�� umiera, na chwil� zmienia si� jego kolor
	for (int i = 0; i < _body.size(); ++i)
	{
		_body[i].setFillColor(sf::Color::Red);
	}
}

bool Snake::IsDead() const
{
	return _dead;
}

float Snake::GetMoveSpeed() const
{
	return _initialMoveInterval / _moveInterval;
}

void Snake::SetFruit(std::shared_ptr<Fruit> fruit)
{
	_fruit = fruit;
}

bool Snake::ReachedMaxSpeed() const
{
	return _moveInterval <= _minMoveInterval;
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (int i = (int)_body.size() - 1; i >= 0; --i)
	{
		target.draw(_body[i]);
	}
}

bool Snake::CanMoveTowards(sf::Vector2i direction) const
{
	if (_body.size() <= 1)
	{
		return true;
	}

	sf::Vector2i headGridPosition = Engine::GetInstance()->WorldPositionToGridPosition(_body[0].getPosition());
	sf::Vector2i secondPartGridPosition = Engine::GetInstance()->WorldPositionToGridPosition(_body[1].getPosition());

	return secondPartGridPosition - headGridPosition != direction;
}