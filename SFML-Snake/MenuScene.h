#pragma once

#include "Scene.h"
#include "Snake.h"

class MenuScene : public Scene
{
public:
	virtual void Init();
	virtual void UpdateInput();
	virtual void Update(float deltaTime);

	// Do wyœwietlania tekstu itp
	std::shared_ptr<sf::Text> startText;
	std::shared_ptr<sf::Text> scoreText;
	std::shared_ptr<sf::Text> controlsText;
	std::shared_ptr<sf::Text> exitText;

	sf::Vector2i windowSize;

private:
	// Do okreœlenia animacji wê¿a w tle
	std::shared_ptr<Snake> snake;

	sf::FloatRect menuSnakePatrolBounds;

	// Do sprawdzania który przycisk jest wybrany
	bool isStartButtonSelected = true;

	bool isExitButtonSelected = false;

	bool isScoreButtonSelected = false;

	bool isControlsButtonSelected = false;
};