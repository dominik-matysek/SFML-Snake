#pragma once

#include "Scene.h"
#include "Snake.h"
#include "Border.h"
#include "Fruit.h"

// Klasa odpowiedzialna za stan rozgrywki
class GameScene : public Scene
{
public:
	virtual void Init();
	virtual void UpdateInput();
	virtual void Update(float deltaTime);

private:
	// Wielko�� kostki w grze (niewidocznej, tak jakby rozmiar piksela)
	sf::Vector2i _gridSize;
	// Obszar zajmowany przez UI (wy�wietlanie liczb� punkt�w, czas, pr�dko��)
	int _gameUiHeight = 100;

	// Obiekty innych klas pojawiaj�ce si� w trakcie rozgrywki
	std::shared_ptr<Border> _border;

	std::shared_ptr<Snake> _player;

	std::shared_ptr<Fruit> _fruit;

	float _timeElapsed = 0.f;
	float _gameOverDelay = 2.f;
	float _gameOverTimer = 0.f;

	// Do wy�wietlania czasu jaki up�yn�� w grze
	std::shared_ptr<sf::Text> _timeText;

	// Do wy�wietlania punkt�w postaci
	std::shared_ptr<sf::Text> _scoreLabel;
	std::shared_ptr<sf::Text> _scoreText;

	// Do wy�wietlania pr�dko�ci postaci
	std::shared_ptr<sf::Text> _speedLabel;
	std::shared_ptr<sf::Text> _speedText;
};