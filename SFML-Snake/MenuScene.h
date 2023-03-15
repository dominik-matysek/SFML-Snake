#pragma once

#include "Scene.h"
#include "Snake.h"

class MenuScene : public Scene
{
public:
	virtual void Init();
	virtual void UpdateInput();
	virtual void Update(float deltaTime);

	// Do wy�wietlania tekstu itp
	std::shared_ptr<sf::Text> startText;
	std::shared_ptr<sf::Text> scoreText;
	std::shared_ptr<sf::Text> controlsText;
	std::shared_ptr<sf::Text> exitText;

	sf::Vector2i windowSize;

private:
	// Do okre�lenia animacji w�a w tle
	std::shared_ptr<Snake> snake;

	sf::FloatRect menuSnakePatrolBounds;

	// Do sprawdzania kt�ry przycisk jest wybrany
	bool isStartButtonSelected = true;

	bool isExitButtonSelected = false;

	bool isScoreButtonSelected = false;

	bool isControlsButtonSelected = false;
};